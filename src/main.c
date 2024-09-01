#include <fxcg/display.h>
#include <fxcg/keyboard.h>
#include <fxcg/file.h>
#include <string.h>

#define SCREEN_WIDTH 384
#define SCREEN_HEIGHT 216

void drawImage(const char *filename)
{
    int file;
    unsigned char buffer[3];
    unsigned int color;
    int x = 0, y = 0;

    unsigned short utf16_filename[256];
    Bfile_StrToName_ncpy(utf16_filename, filename, strlen(filename) + 1);

    // Open the binary file
    file = Bfile_OpenFile_OS(utf16_filename, 0x01, 0); // 0x01 is the mode for read
    if (file < 0)
    {
        PrintXY(1, 1, "No image.bin found", TEXT_MODE_NORMAL, TEXT_COLOR_BLACK);
        return;
    }

    // Read the RGB data and display it pixel by pixel
    while (Bfile_ReadFile_OS(file, buffer, 3, -1) == 3)
    {
        // Convert the 24-bit RGB to the Casio color format
        color = (buffer[0] >> 3) << 11 | (buffer[1] >> 2) << 5 | (buffer[2] >> 3);

        Bdisp_SetPoint_VRAM(x, y, color);

        x++;
        if (x >= SCREEN_WIDTH)
        {
            x = 0;
            Bdisp_PutDisp_DD();

            y++;
            if (y >= SCREEN_HEIGHT)
            {
                break; // Full image painted
            }
        }
    }

    Bfile_CloseFile_OS(file);
}

int main(void)
{
    int key;

    EnableStatusArea(3); // 3 means disable

    // Enable full 16-bit color depth
    Bdisp_EnableColor(1);

    // Clear the screen
    Bdisp_AllClr_VRAM();

    const char *filename = "\\\\fls0\\image.bin";
    drawImage(filename);

    while (1)
    {
        GetKey(&key);

        if (key == KEY_CTRL_EXIT)
        {
            break;
        }
    }

    EnableStatusArea(2); // 2 means enable

    return 0;
}
