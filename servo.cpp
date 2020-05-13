/*
 * sterownik_silnika_krokowego_13.cpp
 *
 * Created: 2018-01-11 19:39:11
 *  Author: Grycek
 */ 
# define F_CPU 1000000UL
#include <stdio.h>
#include <math.h>
#include <avr/io.h>
#include <util/delay.h>

#define C0 PB3  //cewka 0
#define C1 PB0  //cewka 1
#define C2 PB1  //cewka 2
#define C3 PB2  //cewka 3
#define nastawa PB4 //nastawa obrotów

#define t1 50   //czas za³¹czenia cewki
#define t2 0   //czas miêdzy prze³¹czeniem cewek

		int krok1()
		{
		PORTB ^=(1<<C0);   
		_delay_ms(t1);
		PORTB ^=(1<<C0);
		_delay_ms(t2);
		}		
		
		int krok2()
		{
		PORTB ^=(1<<C1);
		_delay_ms(t1);
		PORTB ^=(1<<C1);
		_delay_ms(t2);
		}		
		
		int krok3()
		{
		PORTB ^=(1<<C2);
		_delay_ms(t1);
		PORTB ^=(1<<C2);
		_delay_ms(t2);
		}		
		
		int krok4()
		{
		PORTB ^=(1<<C3);
		_delay_ms(t1);
		PORTB ^=(1<<C3);
		_delay_ms(t2);
		}   
	
	int prawo()
	{
		
	int polozenie_p=1;

		if (polozenie_p>4)
	{polozenie_p==1;}
		

		switch(polozenie_p)
		{
			case 1:			
			krok1();
			
			case 2:			
			krok2();
			
			case 3:			
			krok3();
			
			case 4:			
			krok4();
		}
		polozenie_p++;
	}

	
	
	int lewo()
	{		
		
	int polozenie_l =1;
			
			if (polozenie_l>4)
		{polozenie_l==1;}
			

			switch(polozenie_l)
			{                                                                                                                                             
				case 1:
				krok4();
				
				case 2:
				krok3();
				
				case 3:				
				krok2();
				
				case 4:				
				krok1();
				
			}
			polozenie_l++;
		}
		
				
		
	int main()
	{
	//inicjalizac ja ADC
	ADCSRA =(1<<ADEN) //bit ADEN w rejestrze ADCSRA ustawiony na 1- uruchomienie ADC
	|(1<<ADPS0)
	|(1<<ADPS1)
	|(1<<ADPS2); // Ustawienie preskalera na 128
	ADMUX&=~ (REFS0) ; //ustawienie zewnêtrznego napiêcia odniesienia
	ADMUX |=(1<<MUX1); //ustawienie PB4 jako wejœcie 

	DDRB  |= (1<<C0) | (1<<C1) | (1<<C2) | (1<<C3); //ustawienie jako wyjœcia
	DDRB&=~(1<<DDB4); //ustawienie wejœcia

	ADCSRA|=(1<<ADSC); //wywo³anie dokonania pomiaru
	while(ADCSRA & (1<<ADSC)); //odczekanie a¿ bit ADSC zmieni siê na zero
	
	int polozenie=ADC/85; //dzielenie przez 85, ¿eby uzyskaæ wartoœæ od 0 do 12
	
	for(int i=1;i<=polozenie;i++)
	prawo();
	
	}	