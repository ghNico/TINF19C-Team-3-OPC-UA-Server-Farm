/* This work is licensed under a Creative Commons CCZero 1.0 Universal License.
 * See http://creativecommons.org/publicdomain/zero/1.0/ for more information. */

#include "open62541.h"
#include "parser/parser.hpp"
#include <thread>
#include <pthread.h>
#include <signal.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
void add_attributes_of_internalElements(vector<internal_element> x, UA_NodeId response, UA_Server *server);
UA_NodeId add_variable_to_adressspace(UA_Server *server, const char* descript , const char* dispname , const char* nodeId, UA_String val, UA_NodeId parent);

void add_externalInterfaces(vector<external_interface> x, UA_NodeId response, UA_Server *server);
void add_roleRequirements(vector<role_requirement> x, UA_NodeId response, UA_Server *server);
/* Build Instructions (Linux)
 * - gcc -std=c99 -c open62541.c
 * - g++ server.cpp open62541.o -o server */

using namespace std;


UA_Boolean running = true;

int counter = 0;



static UA_String
nothing = {sizeof(" ") - 1, (UA_Byte *)" "};


auto idValue = 0;

//stop servers
static void stopHandler(int sign) {
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "received ctrl-c");
    running = false;
}

//reads value and header info of attributes and adds them to the selected node
void add_attributes(vector<attribute> x, UA_NodeId response, UA_Server *server){
    for(const auto& y:x){
        //covnert string to UA_String
        UA_String s;
        UA_String_init(&s);
        const char *test = y.value.c_str();
        s.length = strlen(test);
        s.data = (UA_Byte*)test;
        const auto name = y.header.name.c_str();
        const auto des = y.header.description.c_str();
        const auto id = y.header.id.c_str();
        const auto response2 = add_variable_to_adressspace(server, des, name, id, s, response);
        add_attributes(y.attributes, response2, server);
    }
}

//reads header info of internal elements and adds them to the selected node
void add_internalElements(vector<internal_element> x, UA_NodeId response, UA_Server *server){
    for(const auto& y:x){
        const auto name = y.header.name.c_str();
        const auto des = y.header.description.c_str();
        const auto id = y.header.id.c_str();
        const auto response2 = add_variable_to_adressspace(server, des, name, id, nothing, response);
        add_internalElements(y.internal_elements, response2, server);
        add_attributes(y.attributes, response2, server);
        add_externalInterfaces(y.external_interfaces, response2, server);
        add_roleRequirements(y.role_requirements, response2, server);
    }
}

//reads header info of external interfaces and adds them to the selected node
void add_externalInterfaces(vector<external_interface> x, UA_NodeId response, UA_Server *server){
    for(const auto& y:x){
        const auto name = y.header.name.c_str();
        const auto des = y.header.description.c_str();
        const auto id = y.header.id.c_str();
        const auto response2 = add_variable_to_adressspace(server, des, name, id, nothing, response);
        add_externalInterfaces(y.external_interfaces, response2, server);
        add_attributes(y.attributes, response2, server);
    }
}

//adds role requirements to the selected node
void add_roleRequirements(vector<role_requirement> x, UA_NodeId response, UA_Server *server){
    for(const auto& y:x)
        add_externalInterfaces(y.external_interfaces, response, server); 
}


//reads header info of system unit classes and adds them to the selected node
void add_systemUnitClasses(vector<system_unit_class> x, UA_NodeId response, UA_Server *server){
    for(const auto& y:x){
        const auto name = y.header.name.c_str();
        const auto des = y.header.description.c_str();
        const auto id = y.header.id.c_str();
        const auto response2 = add_variable_to_adressspace(server, des, name, id, nothing, response);
        add_internalElements(y.internal_elements, response2, server);
        add_attributes(y.attributes, response2, server);
        add_externalInterfaces(y.external_interfaces, response2, server);
        add_systemUnitClasses(y.system_unit_classes, response2, server);
    }
}

//creates a new node under selected node with description, name, id and value
UA_NodeId add_variable_to_adressspace(UA_Server *server, const char* descript , const char* dispname , const char* nodeId, UA_String val, UA_NodeId parent){
    UA_NodeId myIntegerNodeId;
    if (strlen(nodeId) < 1){
        myIntegerNodeId = UA_NODEID_STRING_ALLOC(1, to_string(counter).c_str());
        counter+=1;    
    }
    else
        myIntegerNodeId = UA_NODEID_STRING_ALLOC(1, nodeId);
    
    UA_VariableAttributes attr = UA_VariableAttributes_default;
    UA_Variant_setScalarCopy(&attr.value, &val, &UA_TYPES[UA_TYPES_STRING]);
    attr.description = UA_LOCALIZEDTEXT_ALLOC("de-DE",descript);
    attr.displayName = UA_LOCALIZEDTEXT_ALLOC("de-DE",dispname);
    UA_QualifiedName myIntegerName = UA_QUALIFIEDNAME_ALLOC(1, dispname);
    UA_NodeId parentReferenceNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES);
    UA_Server_addVariableNode(server, myIntegerNodeId, parent,
                              parentReferenceNodeId, myIntegerName,
                              UA_NODEID_NULL, attr, NULL, NULL);
    /* allocations on the heap need to be freed */
    UA_VariableAttributes_clear(&attr);
    //UA_NodeId_clear(&myIntegerNodeId);
    UA_QualifiedName_clear(&myIntegerName);
    
    return myIntegerNodeId;
}

//stars a server according to a file and on selected port
void launch_server(UA_UInt16 Port, const file file2) {
    signal(SIGINT, stopHandler);
    signal(SIGTERM, stopHandler);
    UA_Server *server = UA_Server_new();
    UA_ServerConfig_setMinimal(UA_Server_getConfig(server), Port, NULL);
    
    for(const auto& y:file2.instance_hierarchies)
        add_internalElements(y.internal_elements, UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER), server);
    
    for(const auto& y:file2.system_unit_class_libs)
        add_systemUnitClasses(y.system_unit_classes, UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER), server);   

    UA_StatusCode retval = UA_Server_run(server, &running);

    UA_Server_delete(server);
    //return retval == UA_STATUSCODE_GOOD ? EXIT_SUCCESS : EXIT_FAILURE;
}

//entry point of program which reads the files and creates threads for the servers
int main(int argc, char** argv){
    ofstream logfile("Test.txt");
    vector<file> files;
    for(int i = 1; i < argc; ++i)
    {
        file f = load_file(argv[i]);
        if(f.instance_hierarchies.size() == 0 && f.system_unit_class_libs.size() == 0){
            logfile << "The file "<< argv[i] << " is not readable, or there is no instance hierachy/system unit class lib to parse" << endl; 
            continue;
        }
        files.push_back(f);
    }

    const auto file_count = files.size();
    vector<thread> threads;
    for (int i = 0; i < file_count; ++i){

        //thread s1(launch_server, 5000 + i, files[i]);

        threads.emplace_back(launch_server, 5000 + i, files[i]);
        logfile << "The file " << files[i].file_name <<" was successfully used to create a server and will be running at port " << (5000 + i) << endl;
    }
    for (int i = 0; i < threads.size(); ++i){
        threads[i].join();
    }

}

