#include <fxcg/display.h>
#include <fxcg/keyboard.h>
#include <fxcg/file.h>
#include <string.h>

#define SCREEN_WIDTH 384
#define SCREEN_HEIGHT 216
#define PIXEL_SIZE 3
#define LINE_BUFFER_SIZE (SCREEN_WIDTH * PIXEL_SIZE)

void drawImage(const char *filename)
{
    int file;
    unsigned char lineBuffer[LINE_BUFFER_SIZE];
    unsigned int color;

    unsigned short utf16_filename[256];
    Bfile_StrToName_ncpy(utf16_filename, filename, strlen(filename) + 1);

    file = Bfile_OpenFile_OS(utf16_filename, 0x01, 0); // Read mode
    if (file < 0)
    {
        PrintXY(1, 1, "image.bin not found", TEXT_MODE_NORMAL, TEXT_COLOR_BLACK);
        return;
    }

    for (int y = 0; y < SCREEN_HEIGHT; y++)
    {
        // Read one full scanline
        if (Bfile_ReadFile_OS(file, lineBuffer, LINE_BUFFER_SIZE, -1) != LINE_BUFFER_SIZE)
        {
            break; // Incomplete image data
        }

        for (int x = 0; x < SCREEN_WIDTH; x++)
        {
            int i = x * PIXEL_SIZE;
            // Convert 24-bit RGB to RGB565
            color = ((lineBuffer[i] & 0xF8) << 8)       // Red
                    | ((lineBuffer[i + 1] & 0xFC) << 3) // Green
                    | (lineBuffer[i + 2] >> 3);         // Blue

            Bdisp_SetPoint_VRAM(x, y, color);
        }
    }

    Bdisp_PutDisp_DD();
    Bfile_CloseFile_OS(file);
}

int main(void)
{
    int key;

    EnableStatusArea(3);  // Hide status area
    Bdisp_EnableColor(1); // Enable full color
    Bdisp_AllClr_VRAM();  // Clear screen

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

    EnableStatusArea(2); // Restore status area
    return 0;
}
