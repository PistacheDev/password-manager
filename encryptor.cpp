// This script is a modified version of this base code for base64 encryption:
// Reynaldev: https://github.com/Reynaldev/Base64.

#include "header.h"
#include <string>
#include <vector>
#include <math.h>

char alphabet(int number)
{
    char alphabet[] = // Alphabet for the encryption in base64.
    {
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
        'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'
    };

    return alphabet[number]; // Return the corresponding character.
};

int baseAlphabet(char character)
{
    if (character == '=') return NULL;

    char alphabet[] = // Alphabet for the decryption from base64.
    {
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
        'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'
    };

    int length = sizeof(alphabet) / sizeof(char);

    for (int i = 0; i < length; i++)
        if (character == alphabet[i])
            return i;

    return -1; // If character not found.
};

std::string encode(std::string input) // Encode in base64 function.
{
    std::vector<int> binary;
    std::string bits; // Turn ASCII code into a binary.

    for (int i = 0; i < input.length(); i++) // Convert the each characters into its binary representation.
        binary.push_back(int(input[i]));

    for (int i = 0; i < binary.size(); i++) // Convert each integer to a binary string.
    {
        std::string string;
        int bit = binary[i];

        while (bit > 0) // Convertion.
        {
            int binary = bit % 2; // The result will be 0 or 1.
            string += std::to_string(binary); // Add the result.
            bit /= 2; // Divide the ASCII character until it reaches zero.
        };

        while (string.length() < 8) // Add leading 0 to make the binary string lenfth 8.
            string += "0";

        for (int j = string.length() - 1; j >= 0; j--) // Append the reversed binary string to the bits string.
            bits += string[j];
    };

    binary.clear();
    std::vector<std::string> binaryString;

    while (bits.length() > 0) // Divide the binary string into 6-bit chunks.
    {
        while (bits.length() < 6) // Correct the length.
            bits += "0";

        std::string elements = bits.substr(0, 6); // Get the six first elements.
        binaryString.push_back(elements); // Add them to the string.
        bits.erase(0, 6); // Delete these elements to continue.
    };

    for (int i = 0; i < binaryString.size(); i++) // Convert the chunks into an integer.
    {
        int result = 0;

        for (int j = binaryString[i].length() - 1; j >= 0; j--)
            if (binaryString[i].at(j) % 2 == 1) // If the binary equals 1, calculate it using the power of two.
                result += pow(2, binaryString[i].length() - 1 - j);

        binary.push_back(result); // Insert the result into the binary vector.
    };

    std::string output;
    int padding = 0;

    for (int i = 0; i < binary.size(); i++)
        output += alphabet(binary[i]); // Alphabet convertion.

    if (binaryString.size() % 4 != 0)
        padding = 4 - (binaryString.size() % 4); // Calculate the number of paddings to add if one segment has less than 4 group.

    while (abs(padding) > 0)
    {
        output += "="; // Add "=" as a padding.
        padding--;
    };

    return output; // Return the encoded value.
};

std::string decode(std::string input) // Decode function.
{
    while (!input.empty() && input.back() == '=') // Remove any equal sign from the input to properly decode it.
        input.pop_back();

    std::vector<int> bits;
    std::string binaryString;

    for (int i = 0; i < input.length(); i++) // Convert each character of the input into its base64 corresponding value.
        bits.push_back(baseAlphabet(input[i]));

    for (int i = 0; i < bits.size(); i++) // Convert each base64 value to its 6-bit binary representation.
    {
        std::string string;

        while (bits[i] > 0)
        {
            int remain = bits[i] % 2;
            string += std::to_string(remain);
            bits[i] /= 2;
        };

        while (string.length() < 6) // Add leading 0 to make the binary string length 6.
            string += "0";

        for (int i = string.length() - 1; i >= 0; i--) // Append the reversed binary string to the binary string.
            binaryString += string[i];
    };

    bits.clear();
    std::vector<std::string> binaryTemp;

    while (binaryString.length() > 0) // Divide the binary string into 8-bit chunck.
    {
        std::string string = binaryString.substr(0, 8); // Get the eight first elements.
        binaryTemp.push_back(string); // Add them to the temp binary.
        binaryString.erase(0, 8); // Delete these elements to continue.
    };

    for (int i = 0; i < binaryTemp.size(); i++) // Convert each 8-bit binary string into an integer.
    {
        int result = 0;

        for (int j = binaryTemp[i].length() - 1; j >= 0; j--)
            if (binaryTemp[i].at(j) % 2 == 1)
                result += pow(2, binaryTemp[i].length() - 1 - j);

        bits.push_back(result);
    };

    std::string output;

    for (int i = 0; i < bits.size(); i++) // Convert each integer to its corresponding ASCII character.
        if (bits[i] != 0)
            output += char(bits[i]);

    return output; // Return the decoded value.
};