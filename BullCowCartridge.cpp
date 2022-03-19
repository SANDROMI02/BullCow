#include "BullCowCartridge.h"
#include "HiddenWordList.h"
//#include "Math/UnrealMathUtility.h"

void UBullCowCartridge::BeginPlay() 
{
    Super::BeginPlay();

    // FBullCowCount Count = {2,3};
    // PrintLine(TEXT("Bulls = %i, Cows = %i"), Count.Bulls, Count.Cows);
    // Count.Bulls = 9;
    // PrintLine(TEXT("Bulls = %i, Cows = %i"), Count.Bulls, Count.Cows);

    Isograms = GetValidWords(Words);

    SetupGame();
}

void UBullCowCartridge::OnInput(const FString& PlayerInput) 
{
    if (bGameOver)
    {
        ClearScreen();
        SetupGame();
        
    }
    else 
    {
        ProcessGuess(PlayerInput);
    }

    //  PrintLine(FString::Printf(TEXT("The HiddenWord is: %s"), *HiddenWord));  BUT WE DONT USE PRINTF CUZ MFS ALREADY CODED IT IN THE FILES
}

void UBullCowCartridge::SetupGame()
{
    HiddenWord = Isograms[FMath::RandRange(0, Isograms.Num() - 1)];
    Lives = HiddenWord.Len() * 2; 
    bGameOver = false;

    //Welcoming The Player
    PrintLine(TEXT("Hi!, welcome to bulls and cows"));
    PrintLine(TEXT("Please press LMB, after that press Tab"));
    PrintLine(TEXT("Guess the %i letter word and Press enter"), HiddenWord.Len());
    PrintLine(TEXT("Lives: %i"), Lives);
    PrintLine(TEXT("Winning Streak: %i"), Streak);
    //PrintLine(TEXT("The HiddenWord is: %s"), *HiddenWord);//Debug line
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("Press Enter to play again"));
   
}

void UBullCowCartridge::ProcessGuess(const FString& Guess)
{
     if (Guess == HiddenWord)
        {
            PrintLine(TEXT("CONGRADULATIONS YOU GUESSED THE WORD"));
            Streak ++;
            EndGame();
            return;
        }

        if(Guess.Len() != HiddenWord.Len())
        {
            PrintLine(TEXT("the word contains: %i letters"), HiddenWord.Len());
            PrintLine(TEXT("try Again"));
            return;
        }

        if(!IsIsogram(Guess))
        {
            PrintLine(TEXT("there are no repeating letters! try again"));
            return;
        }

        else
        {
            PrintLine(TEXT("WRONG!"));
            PrintLine(TEXT("EAT A DICK, you have %i lives left"), --Lives);

            if(Lives <= 0)
            {
                PrintLine(TEXT("which means YOU LOST!!!\nthe word was: %s"), *HiddenWord);
                EndGame();
                Streak = 0;
                return;
            }
        }
    
        FBullCowCount Score = GetBullCows(Guess);

        PrintLine(TEXT("you have %i Bulls and %i Cows"), Score.Bulls, Score.Cows);

}

bool UBullCowCartridge::IsIsogram(const FString& Word) const
{

    for (int32 Index = 0; Index < Word.Len(); Index++)
    {
        for (int32 Comparison = Index + 1; Comparison < Word.Len(); Comparison++)
        {
            if(Word[Index] == Word[Comparison])
            {
                return false;
            }
        }
    }   
    return true;
}
   

TArray<FString>  UBullCowCartridge::GetValidWords(const TArray<FString>& WordList) const
{
        TArray<FString> ValidWords;

        
        for (FString Word : WordList)
        {
            // for (int32 Index = 0; Index < WordList.Num(); Index++)
                  
        
                 if (Word.Len() >=4 && Word.Len()<=8 && IsIsogram(Word))
                {
                
                     ValidWords.Emplace(Word);
            
                 }
        
        }
        return ValidWords;        
 }
 
 FBullCowCount UBullCowCartridge::GetBullCows(const FString& Guess) const
 {
    FBullCowCount Count;

     for (int32 GuessIndex = 0; GuessIndex < Guess.Len(); GuessIndex++)
     {
        if(Guess[GuessIndex] == HiddenWord[GuessIndex])
        {
            Count.Bulls++;
            continue;
        }
        for (int32 HiddenIndex = 0; HiddenIndex < HiddenWord.Len(); HiddenIndex++)
        {
            if(Guess[GuessIndex] == HiddenWord[HiddenIndex])
            {
                Count.Cows++;
                break;
            }
        }
     }   
     return Count;
 }
