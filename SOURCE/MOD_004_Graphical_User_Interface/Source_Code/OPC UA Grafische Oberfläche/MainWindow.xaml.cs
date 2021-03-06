﻿using System;
using System.Collections.Generic;
using System.Collections;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.IO;
using Microsoft.Win32;
using Path = System.IO.Path;

namespace OPC_UA_Grafische_Oberfläche
{



    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        string[] FileLst = new string[10];
        int i = new int();
        string path;
        int errorline = new int();
        private readonly List<TextBox> files;

        /// <summary>
        /// Function which is called when the application starts.
        /// Load all textBoxes into variable files; Updates the Textbox(updateVisualLst)
        /// </summary>
        public MainWindow()
        {
            InitializeComponent();
            files = new List<TextBox> { txtFile1, txtFile2, txtFile3, txtFile4, txtFile5, txtFile6, txtFile7, txtFile8, txtFile9, txtFile10 };
            updateVisualLst();
        }


        /// <summary>
        /// Function which is called by the reset Button.
        /// Set FileLst = null; Updates the Textbox(updateVisualLst); Logs that the File is deleted
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void BtnResetFile_Click(object sender, RoutedEventArgs e)
        {
            for (int l = 0; l < 10; l++)
            {
                FileLst[l] = null;
            }
            i = 0;
            updateVisualLst();
            errorline++;
            LogTxt.Text += Environment.NewLine + errorline + "  Imported Files were deleted " + Environment.NewLine;
        }

        /// <summary>
        /// Function which is called by the add Button.
        /// openFileDialog -> path of selected file is writen into the List of all selected Files; Logging if it is failed or added; Updates TxtBoxes.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void AddFile_Click(object sender, RoutedEventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            if (openFileDialog.ShowDialog() == true)
                path = openFileDialog.FileName;
            if (i < 10)
            {
                string typ = Path.GetExtension(path);
                if (typ == ".aml")
                {
                    FileLst[i] = path;
                    errorline++;
                    LogTxt.Text += errorline + "  " + openFileDialog.FileName + " was added.....";
                    LogTxt.Text += Environment.NewLine;
                    i++;
                    MessageTxt.Text = "";
                }
                else
                {
                    MessageTxt.Text = "WARNING: You can only insert AML-Files!";
                    errorline++;
                    LogTxt.Text += errorline + "  ERROR: Failed Loading File: (" + path + ")! You can only load AML Files.";
                    LogTxt.Text += Environment.NewLine;
                }
            }
            else
            {
                errorline++;
                LogTxt.Text += Environment.NewLine + errorline + "  ERROR: You can only select 10 Files" + Environment.NewLine;
            }

            updateVisualLst();
        }

        /// <summary>
        /// Updates all TextBoxes with the FileName which is selected (if an file is selected with the same index as the TextBox)
        /// </summary>
        private void updateVisualLst()
        {
            Image myImage3 = new Image();
            BitmapImage bi3 = new BitmapImage();
            bi3.BeginInit();
            bi3.UriSource = new Uri("/delete_transparent.png", UriKind.Relative);
            bi3.EndInit();


            files.ForEach(file => file.Text = "");
            for (int index = 0; index < i; index++)
                files[index].Text = $"File {index + 1}: " + FileLst[index];
        }

        private void Button_Click_1(object sender, RoutedEventArgs e)
        {
            /// Start Service 
        }

    }
}
