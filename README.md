# Image-Style-Converter-C
This is a program that takes an image and returns it with a filter applied

To run the program, you need to provide a PPM image with the following format:

1. First Line:
   The format of the image (e.g., P3).

2. Second Line:
   The dimensions of the image (width and height).

3. Third Line:
   The maximum pixel value.

4. Subsequent Lines:
   The pixel values should be listed after the above information.

         P3          - Format
         1280 853    - Dimensions
         255         - Max value
         4          
         5
         7
         4
         5
         7
         ...


# Instructions for Running the Program

To compile and run the program, follow the steps below:

Open the terminal in the directory where your main.c file is located.

Compile the program using the following command:

    gcc -o <your_program_name> main.c

Or use any other command you prefer.

Replace <your_program_name> with your desired name for the executable.

After successful compilation, run the program with the following command:

    ./<your_program_name>
        
Make sure to replace <your_program_name> with the name you chose.


Program Output

This process will generate an image named output_image.ppm. You can open it using your preferred image viewer software. Alternatively, if you are using Visual Studio Code, you can download the 'PPM View' extension to easily view PPM files directly in the editor.


