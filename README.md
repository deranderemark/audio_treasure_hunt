# audio_treasure_hunt
*Template for an audio treasure hunt using an Arduino Uno and the Adafruit Mp3-Shield as well as some audio files.*

This code provides the basis for an audio treasure hunt inspired by https://www.instructables.com/Audio-Treasure-Hunt/ and https://www.youtube.com/watch?v=CC1LJgOTENY .
They both use the waveshield by Adafruit which wasn't in stock when I wanted to build my version wherefore I edited the code to be compatible with the Adafruit MusicMaker Mp3 Shield instead.

I used the code by instructables but made some changes. Mainly, I stored the secretCodes into a multidimensional array. This enables me to iterate over all of them instead of 
stacking multiple conditional statements after eachother. It is easier to add more secretCodes afterwards this way. Link to Repository: https://github.com/deranderemark/audio_treasure_hunt
