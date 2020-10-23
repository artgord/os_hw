#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>

int main(int argc, char* argv[])
{
    //end programm
    if (argc < 3)
    {
        std::cout << "Invalid arguments\n";
        return -1;
    }

    //read only
    int file = open(argv[1], O_RDONLY);

    //if file is incorrect
    if (file == -1)
    {
        std::cout << "Cannot open file...\n";
        exit(errno); //end programm + error
    }


    int writeFile = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP);

    if (writeFile == -1) {
        std::cout << "Cannot open file...\n";
        exit(errno); //end programm + error
    }

    //we will need these in lseek()
    long long hole = 0, data = 0, offset = 0;
    //s - sorce, dest - destindation
       //we keep their sizes to print in the end
    long long s_logical = 0, dest_logical = 0,
        s_physical = 0, dest_physical = 0;

    //we will copy data from 'source' file to 'destination' file using this array of chars
    char* buffer = new char[0];
    long buff_Size = 0;

    //our main programm
    while (true)
    {
        //SEEK_HOLE - it will stop when he find a hole
        //in file, find hole starting from offset)
        hole = lseek(file, offset, SEEK_HOLE);

        //logical size - only data, without holes
        //(hole - data) == size of data that was before the hole
        s_physical += hole - data;
        offset = hole;

        //resizing our buffer
        buff_Size = hole - data;
        buffer = new char[buff_Size];

        //going left by buff_Size to read data in buffer
        lseek(file, -buff_Size, SEEK_CUR);
        read(file, buffer, buff_Size); // reading data
        dest_physical += write(writeFile, buffer, buff_Size); //copying into 'destination' file



        data = lseek(file, offset, SEEK_DATA);
        //seeking for data

        //if data has ended - break out of a cycle
        if (data == -1)
        {
            if (errno == ENXIO)
            {
                //add the hole at the end of the file
                data = lseek(file, 0, SEEK_END);  //data points on the end of the file
                lseek(writeFile, data - hole, SEEK_END);

                //(data - hole) == size of hole
                dest_logical += data - hole;

                //there always minimum 1 hole at the end of the file
                break;
            }
            //if cycle didn't break, then... what just happened?
            else {
                std::cout << "Something went wrong...\n";
                return -1;
            }
        }

        s_logical += data - hole;
        offset = data;

        //copy the hole to the destination file
        lseek(writeFile, data - hole, SEEK_END);
        dest_logical += data - hole;
    }

    std::cout << "Source logical: " << s_logical << "; source physical: " << s_physical << ";\n";
    std::cout << "Destination logical: " << dest_logical << "; destination physical: " << dest_physical << ";";;
}