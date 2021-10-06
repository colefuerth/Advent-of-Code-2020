using System;

namespace day15_2
{
    class Program
    {
        // returns the index of the number it found, -1 means not found
        static long searchArray(long[] arr, long length, long search)
        {
            for (long i = length - 2; i >= 0; i--) if (arr[i] == search) return i;
            return -1;
        }

        public long currentPlace(long currentPos)
        {
            return currentPos % 1000;
        }
        static void Main(string[] args)
        {
            long target = 30000000;
            long[] input = { 16, 1, 0, 18, 12, 14, 19 };
            long inputLength = input.Length;
            System.Console.WriteLine("inputLength is "+ inputLength+"\n");
            System.Console.WriteLine("Declaring arr...");
            long[] arr = new long[target]; // memory set for question
            System.Console.WriteLine("done.\n");
            long currentTurn;  // current turn, ah yes very descriptive
            System.Console.WriteLine("assigning the first "+ inputLength+" values...");
            for (long i = 0; i < inputLength; i++) arr[i] = input[i];  // empty the initial input into the mem array
            System.Console.WriteLine("done.\n");
            // start of main code
            for (currentTurn = inputLength; currentTurn < target; currentTurn++)
            {
                long temp = searchArray(arr, currentTurn, arr[currentTurn - 1]);
                if (temp == -1) arr[currentTurn] = 0;
                else if (arr[currentTurn - 1] == arr[currentTurn - 2]) arr[currentTurn] = 1;
                else arr[currentTurn] = currentTurn - 1 - temp;
                if (currentTurn % 100000 == 0) System.Console.WriteLine("reached " + currentTurn+"\n");
            }

            //System.Console.WriteLine("the %ldth spoken number is %ld\n", target, arr[target]);
            System.Console.WriteLine("the " + target + "th spoken number is " + arr[target-1] + "\n");
        }
    }
}
