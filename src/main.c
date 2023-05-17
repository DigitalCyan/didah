#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

Mix_Chunk *gTone;

char *gMorse[] = {
    ".-",     // A
    "-...",   // B
    "-.-.",   // C
    "-..",    // D
    ".",      // E
    "..-.",   // F
    "--.",    // G
    "....",   // H
    "..",     // I
    ".---",   // J
    "-.-",    // K
    ".-..",   // L
    "--",     // M
    "-.",     // N
    "---",    // O
    ".--.",   // P
    "--.-",   // Q
    ".-.",    // R
    "...",    // S
    "-",      // T
    "..-",    // U
    "...-",   // V
    ".--",    // W
    "--..--", // X
    "-.--",   // Y
    "--..",   // Z
};

void MORSE_Init()
{
    SDL_Init(SDL_INIT_AUDIO);
    Mix_Init(MIX_INIT_OGG);

    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 2048);

    gTone = Mix_LoadWAV("assets/tone.ogg");
    if (gTone == NULL)
    {
        puts(Mix_GetError());
        return;
    }
}

void MORSE_PlayChar(char c)
{
    switch (c)
    {
    case '.':
        Mix_PlayChannel(1, gTone, 0);
        break;

    case '-':
        Mix_PlayChannel(1, gTone, 2);
        break;

    case ' ':
        SDL_Delay(300);
        break;

    default:
        break;
    }

    while (Mix_Playing(1) != 0)
    {
        SDL_Delay(10);
    }

    SDL_Delay(100);
}

void MORSE_PlayMorse(char *morse)
{
    while (*morse != '\0')
    {
        MORSE_PlayChar(*morse);
        morse++;
    }
}

void MORSE_PlayString(char *text)
{
    while (*text != '\0')
    {
        char c = *text;

        if (!islower(c) && !isupper(c) && !isspace(c))
        {
            text++;
            continue;
        }

        if (isspace(c))
        {
            MORSE_PlayChar(' ');
            text++;
            continue;
        }

        if (islower(c))
        {
            c = toupper(c);
        }

        uint8_t index = c - 65;
        MORSE_PlayMorse(gMorse[index]);
        SDL_Delay(200);

        text++;
    }
}

int main(int argc, char *args[])
{
    MORSE_Init();

    if(!isatty(fileno(stdin))) {
      char buffer[1024];
      while(fgets(buffer, sizeof(buffer), stdin) != NULL) {
        MORSE_PlayString(buffer);
      }

      return 0;
    }

    if (argc != 2)
    {
        puts("Invalid argument count");
        puts("Usage: didah <text>");
        return 1;
    }

    MORSE_PlayString(args[1]);

    return 0;
}
