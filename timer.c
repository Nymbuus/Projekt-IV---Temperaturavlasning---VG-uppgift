/********************************************************************************
* timer.c: Innehåller funktioner realterade till timern.
********************************************************************************/
#include "header.h"

// Vad timern ska räkna upp till.
static uint32_t timer0_max = 0;

// Deklarerar funktion.
static uint32_t average(const uint32_t* data, 
                        const uint8_t size);

/********************************************************************************
* set_timer0_max: Initierar timern med en angiven tid den ska räkna till.
********************************************************************************/
void set_timer0_max(const double time_ms)
{
   timer0_max = (uint32_t)(time_ms / 0.128 + 0.5);
   return;
}

/********************************************************************************
* set_timer0_max: Skickar tillbaka timerns tid den ska räkna till.
********************************************************************************/
uint32_t get_timer0_max(void)
{
   return timer0_max;
}

/********************************************************************************
* push_counter_time: fem stycken tidsvärden skickas in i funktionen beroende på
*                    tidsintervallen mellan knapptrycken. När detta har gjorts
*                    räknas medelvärdet ut genom en funktion och array börjar om
*                    på nytt.
********************************************************************************/
void push_counter_time(volatile uint32_t* counter_time)
{ 
   static uint32_t timerarray_s[5];
   static uint8_t index = 0;
   
   timerarray_s[index++] = *counter_time;
   *counter_time = 0;

   // Genomsnittstiden räknas ut med en funktion när 5 värden har lagts in i arrayen.
   if (index >= 5)
   {
      timer0_max = average(timerarray_s, 5);
      index = 0;
   }
}

/********************************************************************************
* average: Räknar ut medelvärdet i arrayen och skickar tillbaka det som
*          returvärde.
********************************************************************************/
static uint32_t average(const uint32_t* data, 
                        const uint8_t size)
{
   uint32_t sum = 0;

   for (uint8_t i = 0; i < size; ++i)
   {
      sum += data[i];
   }

   return (uint32_t)(sum / (double)size + 0.5);
}