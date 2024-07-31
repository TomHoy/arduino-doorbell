/*
Original program by Robson Couto, 2019
Updated module with looping, code cleanup, and button detection by Tom Hoy, 2024
*/

/*

User-Definable Variables:

- tempo: The speed of the melody, the higher the number, the slower the melody.
- button: The pin that the button is connected to.
- buzzerarr: The pin(s) that the hot wire of the buzzer(s) is/are connected to.
- loopTimeMax: How many times to *play* (not loop) the melody when the button is pressed.

- randNumber: Increase this value if you add more melodies to the program.
- The various arrays: Add your own melodies to the program in the form of an array outlined below.

*/

//Define the notes as their frequencies.
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
#define REST      0


//Initalises the input button variable.
const int button = D0;
int buttonPush;

// change this to whichever pin you want to use
int buzzerarr[] = { D7, D8 };

// notes of the moledy followed by the duration.
// a 4 means a quarter note, 8 an eighteenth , 16 sixteenth, so on
// !!negative numbers are used to represent dotted notes,
// so -4 means a dotted quarter note, that is, a quarter plus an eighteenth!!


// We want to take our three melodies, and using our RNG set one of them to be the melody int to be used later.

//Initalise the button as an input.
void setup() {
  pinMode(button, INPUT);

  //Pulls a seed from the atmospheric noise of the analogue pin, best RNG we can do with the hardware we have.
  randomSeed(analogRead(0));
}


// RNG Number initalising, this declares our randNumber, melodySize, and tempo variables, while initalising melody as a pointer to an array.
int randNumber;
int tempo;

// Loop time initalisation, specified in switch.
int loopTimeMax;

int *melody;
int melodySize; // These two help us later on declare melody sizes and stuff.


void melodyloop() {

// Main RNG logic, we take our random number from before and feed it into our switch statement, depending on the output, we select which melody to load into the melody array memory.
// Do note, as each array is of a custom size, we need to tell the memory controller to allocate (and unallocate) the correct amount of memory for each melody.
// Once the memory is allocated, we set the tempo, then break from the statement.
// !! There is a much, much more clean way of doing this! I'll be switching to it in the future, but for now it works, and that's the important part. !!
// Eventually make it a lookup table or similar, I also don't want to store the arrays in the switch statement, this progressively increases the load on the arduino this program places, and it's not good practice.

// The below is a bit messy, so see the following for an exmaple on how to add your own melodies to the program: (Be sure to increase the random number range to accomodate for the new melody)

/*

case #: {
static int melodyNameHere[] = {
  // Put your notes here, format is listed above
  NOTE_EXAMPLE,4
};
melodySize = sizeof(melodyNameHere) / sizeof(melodyNameHere[0]);
melody = (int *)malloc(melodySize * sizeof(int));
memcpy(melody, melodyNameHere, melodySize * sizeof(int));

loopTimeMax = 2; // How many times to play the song, if unspecified it will play with the previously set one, do change it!
tempo = 123; // Put the tempo of the music here
break; // Return from code
}

*/

randNumber = random(1, 8); // We take a random number, the max is one less than visible.

switch (randNumber) {
    case 1: {
    static int melodyMario[] = {
        // Mario Bros Game Over Theme
        NOTE_C5,-4, NOTE_G4,-4, NOTE_E4,4,
        NOTE_A4,-8, NOTE_B4,-8, NOTE_A4,-8, NOTE_GS4,-8, NOTE_AS4,-8, NOTE_GS4,-8,
        NOTE_G4,8, NOTE_D4,8, NOTE_E4,-2,
    };
    // Define a pointer and dynamically allocate memory to store the melody! (Remember, we're the garbage collection here)
    melodySize = sizeof(melodyMario) / sizeof(melodyMario[0]); // The melodySize is simply the size of the array, divided by the size of the first element in the array. (I don't fully understand why it's necessary, but without it it breaks so keep it, please.)
    melody = (int *)malloc(melodySize * sizeof(int)); // Allocate memory for the melody based on the size of the array.
    memcpy(melody, melodyMario, melodySize * sizeof(int)); // Copy the melody into the allocated memory based on the size of the array and location.
    
    // How many times to *play* (not loop, it will play x amount of times as listed below) the melody, adds a pause between loops as well.
    loopTimeMax = 2;
    tempo = 200; // Define custom tempo for each theme
    break; // Return from statement
    }
    case 2: {
    static int melodyTetris[] = {
        // Tetris Theme
        NOTE_E5, 4,  NOTE_B4,8,  NOTE_C5,8,  NOTE_D5,4,  NOTE_C5,8,  NOTE_B4,8,
        NOTE_A4, 4,  NOTE_A4,8,  NOTE_C5,8,  NOTE_E5,4,  NOTE_D5,8,  NOTE_C5,8,
        NOTE_B4, -4,  NOTE_C5,8,  NOTE_D5,4,  NOTE_E5,4,
        NOTE_C5, 4,  NOTE_A4,4,  NOTE_A4,4,  REST,8,
    };

    // Once again defining a pointer and dynamic memory allocation
    melodySize = sizeof(melodyTetris) / sizeof(melodyTetris[0]);
    melody = (int *)malloc(melodySize * sizeof(int));
    memcpy(melody, melodyTetris, melodySize * sizeof(int));

    loopTimeMax = 2;
    tempo = 144;
    break;
    }
    case 3: {
    static int melodyNokia[] = {
        // Nokia Ringtone
        NOTE_E5, 8, NOTE_D5, 8, NOTE_FS4, 4, NOTE_GS4, 4,
        NOTE_CS5, 8, NOTE_B4, 8, NOTE_D4, 4, NOTE_E4, 4,
        NOTE_B4, 8, NOTE_A4, 8, NOTE_CS4, 4, NOTE_E4, 4,
        NOTE_A4, 2,
    };

    melodySize = sizeof(melodyNokia) / sizeof(melodyNokia[0]);
    melody = (int *)malloc(melodySize * sizeof(int));
    memcpy(melody, melodyNokia, melodySize * sizeof(int));

    loopTimeMax = 2;
    tempo = 235;
    break;
    }
    case 4: {
      static int melodyDoom[] = {
        // E1M1 Theme
        NOTE_E2, 8, NOTE_E2, 8, NOTE_E3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_D3, 8, NOTE_E2, 8, NOTE_E2, 8,
        NOTE_C3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_AS2, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_B2, 8, NOTE_C3, 8,
        NOTE_E2, 8, NOTE_E2, 8, NOTE_E3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_D3, 8, NOTE_E2, 8, NOTE_E2, 8,
        NOTE_C3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_AS2, -2,

        NOTE_E2, 8, NOTE_E2, 8, NOTE_E3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_D3, 8, NOTE_E2, 8, NOTE_E2, 8,
        NOTE_C3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_AS2, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_B2, 8, NOTE_C3, 8,
        NOTE_E2, 8, NOTE_E2, 8, NOTE_E3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_D3, 8, NOTE_E2, 8, NOTE_E2, 8,
        NOTE_C3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_AS2, -2,
      };

      melodySize = sizeof(melodyDoom) / sizeof(melodyDoom[0]);
      melody = (int *)malloc(melodySize * sizeof(int));
      memcpy(melody, melodyDoom, melodySize * sizeof(int));

      loopTimeMax = 1;
      tempo = 225;
      break;
    }
    case 5: {
      static int melodyMarioMain[] = {
        // Mario Bros 1 Theme
        NOTE_E5,8, NOTE_E5,8, REST,8, NOTE_E5,8, REST,8, NOTE_C5,8, NOTE_E5,8,
        NOTE_G5,4, REST,4, NOTE_G4,8, REST,4,
        NOTE_C5,-4, NOTE_G4,8, REST,4, NOTE_E4,-4,
        NOTE_A4,4, NOTE_B4,4, NOTE_AS4,8, NOTE_A4,4,
        NOTE_G4,-8, NOTE_E5,-8, NOTE_G5,-8, NOTE_A5,4, NOTE_F5,8, NOTE_G5,8,
        REST,8, NOTE_E5,4,NOTE_C5,8, NOTE_D5,8, NOTE_B4,-4,
      };

      melodySize = sizeof(melodyMarioMain) / sizeof(melodyMarioMain[0]);
      melody = (int *)malloc(melodySize * sizeof(int));
      memcpy(melody, melodyMarioMain, melodySize * sizeof(int));

      loopTimeMax = 2;
      tempo = 200;
      break;
    }
    case 6: {
      static int melodyMiiChannel[] = {
        // Nintendo Wii Mii Channel Theme
        NOTE_FS4,8, REST,8, NOTE_A4,8, NOTE_CS5,8, REST,8,NOTE_A4,8, REST,8, NOTE_FS4,8,
        NOTE_D4,8, NOTE_D4,8, NOTE_D4,8, REST,8, REST,4, REST,8, NOTE_CS4,8,
        NOTE_D4,8, NOTE_FS4,8, NOTE_A4,8, NOTE_CS5,8, REST,8, NOTE_A4,8, REST,8, NOTE_F4,8,
        NOTE_E5,-4, NOTE_DS5,8, NOTE_D5,8, REST,8, REST,4,

        NOTE_GS4,8, REST,8, NOTE_CS5,8, NOTE_FS4,8, REST,8,NOTE_CS5,8, REST,8, NOTE_GS4,8,
        REST,8, NOTE_CS5,8, NOTE_G4,8, NOTE_FS4,8, REST,8, NOTE_E4,8, REST,8,
        NOTE_E4,8, NOTE_E4,8, NOTE_E4,8, REST,8, REST,4, NOTE_E4,8, NOTE_E4,8,
        NOTE_E4,8, REST,8, REST,4, NOTE_DS4,8, NOTE_D4,8,
      };

      melodySize = sizeof(melodyMiiChannel) / sizeof(melodyMiiChannel[0]);
      melody = (int *)malloc(melodySize * sizeof(int));
      memcpy(melody, melodyMiiChannel, melodySize * sizeof(int));

      loopTimeMax = 1;
      tempo = 114;
      break;
    }
    case 7: {
      static int melodyZelda[] = {
        // Song of Storms from Ocarina of Time
        NOTE_D4,4, NOTE_A4,4, NOTE_A4,4,
        REST,8, NOTE_E4,8, NOTE_B4,2,
        NOTE_F4,4, NOTE_C5,4, NOTE_C5,4,
        REST,8, NOTE_E4,8, NOTE_B4,2,
        NOTE_D4,4, NOTE_A4,4, NOTE_A4,4,
        REST,8, NOTE_E4,8, NOTE_B4,2,
        NOTE_F4,4, NOTE_C5,4, NOTE_C5,4,
        REST,8, NOTE_E4,8, NOTE_B4,2,
        NOTE_D4,8, NOTE_F4,8, NOTE_D5,2,
      };

      melodySize = sizeof(melodyZelda) / sizeof(melodyZelda[0]);
      melody = (int *)malloc(melodySize * sizeof(int));
      memcpy(melody, melodyZelda, melodySize * sizeof(int));

      loopTimeMax = 1;
      tempo = 108;
      break;
    }
}



  // Moving code from above into this loop as it needs to re-calculate the melody each time.

  // sizeof gives the number of bytes, each int value is composed of two bytes (16 bits)
  // there are two values per note (pitch and duration), so for each note there are four bytes
 // int notes = sizeof(melody) / sizeof(melody[0]) / 2;

  int notes = melodySize / 2;  // We already calculated the array size earlier, why not try using that information?


  // this calculates the duration of a whole note in ms
  int wholenote = (60000 * 4) / tempo;

  int divider = 0, noteDuration = 0;

  // iterate over the notes of the melody.
  // Remember, the array is twice the number of notes (notes + durations)

  // Enclose entire loop inside another loop for time looping

  for (int loopTime = 0; loopTime < loopTimeMax; loopTime++) {
  
    for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

      // calculates the duration of each note
      divider = melody[thisNote + 1];
      if (divider > 0) {
        // regular note, just proceed
        noteDuration = (wholenote) / divider;
      } else if (divider < 0) {
        // dotted notes are represented with negative durations!!
        noteDuration = (wholenote) / abs(divider);
        noteDuration *= 1.5; // increases the duration in half for dotted notes
      }

      for (int buzzer : buzzerarr) {
        tone(buzzer, melody[thisNote], noteDuration * 0.9);
      }

      // Wait for a specific duration before laying the next note. (Influenced by tempo)
      delay(noteDuration);

      // Stop the waveform generation before processing the next note
      for (int buzzer : buzzerarr) {
        noTone(buzzer);
      }
    }
    // Pauses the melody between loops, allowing a more "seamless" transisiton between repeats.
    delay(500);
  }
    // Garbage collection, frees up the memory used by the melody to avoid memory leaks.
    free(melody);
}

// Sets the button status to initally be unheld, allow the program to play a tone, even if the button was previously pressed before boot.
int heldStatus = 0;

// Primary program loop, ensures that the melody only plays once when the button is pressed and held.
void loop() {
    if (digitalRead(button) == HIGH) {
      // We need to stall the processor for 0.1 seconds due to the fact that the button is slightly sticky when retracting and can cause a race condition.
      delay(100);
      // Checks the if the button is pressed, and it is not currently held, play the melody.
        if (heldStatus == 0) {
          melodyloop();
        }
        // Increment the held counter while the button remains held, this ensures that the melody only plays once until the button is released and pressed again.
        heldStatus++;
    }
    else {
      // Reset the held counter to 0 once the button is released, allowing the melody to play again.
        heldStatus = 0;
    }
}