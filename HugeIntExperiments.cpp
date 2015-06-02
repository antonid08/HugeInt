// HugeIntExperiments.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include <math.h>

class hugeInt
{

	//----------------------------------------------------------*Поля*------------------------------------------------------------//
private:
	int length;
	short* digits;
	//----------------------------------------------------------*Поля*------------------------------------------------------------//
public:
	int getLength(){
		return length;
	}

	void setDigits(int position, int digit){
		digits[position] = digit;	
	}
	//-------------------------------------------------------*Конструктор пустого числа заданой длины----------------------------------------//
	hugeInt(int l)
	{
		length = l;
		digits = new short[length];
		for (int i = length; i > 0; i--){
			digits[i] = 0;
		}
	}
	//-------------------------------------------------------*Конструктор пустого числа заданой длины----------------------------------------//

	//-------------------------------------------------------*Конструктор числа при вводе с клавиатуры----------------------------------------//	
	hugeInt()
	{
		input();
	}
	//-------------------------------------------------------*Конструктор числа при вводе с клавиатуры----------------------------------------//	
	
	 //-------------------------------------------------------*Конструктор числа с заданным значением----------------------------------------//
    hugeInt(std::string d)
    {
        length = d.length();
		digits = new short[length];
		
		for (int i = 0; i < length; i++){
			digits[i] = d[length - i - 1] - '0';
		}
    }
    //-------------------------------------------------------*Конструктор числа с заданным значением-----------------------------------//

	//-------------------------------------------------------*Рандом-------------------------------------------------------------------------//
	void random(int len){
		length = len;
		for (int i = 0; i < len; i++){
			digits[i] = rand() % 9 + 1;
		}
	}
	//-------------------------------------------------------*Рандом-------------------------------------------------------------------------//	
	
	//-------------------------------------------------------*Печать-------------------------------------------------------------------------//	
		void print(){
		for (int i = 0; i < length; i++){
			std::cout<<digits[length - i - 1];
		}
		std::cout<<std::endl;
	}
	//-------------------------------------------------------*Печать-------------------------------------------------------------------------//	
	
	//-------------------------------------------------------*Сравнение-------------------------------------------------------------------------//	
	
	int compareHuge(hugeInt a, hugeInt b){
		if(a.length > b.length) return 1;
		if(a.length < b.length) return -1;

	    for (int i = length - 1; i >= 0; i--  ){
			if(a.digits[i] < b.digits[i]) return -1;
			if(a.digits[i] > b.digits[i]) return 1;
		}
		return 0;
	}
	//-------------------------------------------------------*Сравнение-------------------------------------------------------------------------//	
	
	//-------------------------------------------------------*Оператор <= -------------------------------------------------------------------------//	
	bool operator  <= (hugeInt b){
		if (length < b.length)
			return true;
		if (length > b.length)
			return false;

		for (int i = length - 1; i >= 0; i--){
			if (digits[i] < b.digits[i])
				return true;
			else if(digits[i] > b.digits[i])
				return false;
		}
		return true;
	}
	//-------------------------------------------------------*Оператор <= -------------------------------------------------------------------------//	

	//-------------------------------------------------------*Оператор >= -------------------------------------------------------------------------//	
	bool operator  >= (hugeInt b){
		if (length < b.length)
			return false;
		if (length > b.length)
			return true;
		
		for (int i = length - 1; i >= 0; i--){
			if (digits[i] < b.digits[i])
				return false;
			else if(digits[i] > b.digits[i])
				return true;
		}
		return true;
	}
	//-------------------------------------------------------*Оператор >= -------------------------------------------------------------------------//	

	//-------------------------------------------------------*Оператор < -------------------------------------------------------------------------//	
	bool operator  < (hugeInt b){
		if (length < b.length)
			return true;
		if (length > b.length)
			return false;
		for (int i = length -1; i >= 0; i--){
			if (digits[i] > b.digits[i])
				return false;
			else if (digits[i] < b.digits[i])
				return true;
		}
		return false;
	}
	//-------------------------------------------------------*Оператор < -------------------------------------------------------------------------//	

		//-------------------------------------------------------*Оператор > -------------------------------------------------------------------------//	
	bool operator  > (hugeInt b){
		if (length < b.length)
			return false;
		if (length > b.length)
			return true;
		for (int i = length -1; i >= 0; i--){
			if (digits[i] > b.digits[i])
				return true;
			else if (digits[i] < b.digits[i])
				return false;
		}
		return false;
	}
	//-------------------------------------------------------*Оператор > -------------------------------------------------------------------------//	
		
	//-------------------------------------------------------*Оператор == -------------------------------------------------------------------------//	
	bool operator == (hugeInt b){
		if (length != b.length)
			return false;
		for (int i = length - 1; i >= 0; i--)
			if (digits[i] != b.digits[i])
				return false;
		return true;
	}
	//-------------------------------------------------------*Оператор == -------------------------------------------------------------------------//	

	//-------------------------------------------------------*Оператор = HugeInt -------------------------------------------------------------------------//	
	hugeInt operator = (hugeInt b){
		length = b.length;
		for (int i = 0; i < b.length; i++){
			digits[i] = 0;
			digits[i] = b.digits[i];
		}
		return *this;
	}
	//-------------------------------------------------------*Оператор = HugeInt-------------------------------------------------------------------------//

	//-------------------------------------------------------*Оператор = int -------------------------------------------------------------------------//	
	hugeInt operator = (int b){
		int bLength = 0;
		int temp = b;
		do{
			b /= 10;
			bLength++;
		}while (b != 0);
		int divisor = 10;
		length = bLength;
		for (int i = 0; i < length; i++){
			digits[length - i - 1] = temp % divisor;
			divisor *= 10;
		}
		return *this;
	}
	//-------------------------------------------------------*Оператор = int -------------------------------------------------------------------------//	
	
	
	//-------------------------------------------------------*Оператор +  -------------------------------------------------------------------------//	
	hugeInt operator + (hugeInt b){

		int newLength;
		if (compareHuge(*this, b) == 1)
			newLength = length + 1;
		else
			newLength = b.length + 1;

		hugeInt tempA(newLength);
		hugeInt tempB(newLength);

		for(int i = 0; i < newLength; i++){
			tempA.digits[i] = 0;
			tempB.digits[i] = 0;
		}
		for(int i = 0; i < b.length; i++)
			tempB.digits[i] = b.digits[i]; 
		for (int i = 0; i < length; i++)
			tempA.digits[i] = digits[i];

		for (int ix = 0; ix < newLength; ix++)
		{
			tempB.digits[ix] += tempA.digits[ix]; // суммируем последние разряды чисел
			tempB.digits[ix + 1] += (tempB.digits[ix] / 10); // если есть разряд для переноса, переносим его в следующий разряд
			tempB.digits[ix] %= 10; // если есть разряд для переноса он отсекается
		}
		tempB.length = newLength;
		if (tempB.digits[newLength - 1] == 0)
			tempB.length -= 1;
	
		return tempB;
	}
	//-------------------------------------------------------*Оператор + -------------------------------------------------------------------------//	

	//-------------------------------------------------------*Оператор - -------------------------------------------------------------------------//	
	hugeInt operator-(hugeInt b){
		int newLength;
		if (compareHuge(*this, b) == 1){
			newLength = length ;
		}else{
			newLength = b.length;
		}
		
		hugeInt result(newLength);
		hugeInt newB(newLength);

		for (int i = 0; i < newLength; i++){
			result.digits[i] = 0;
			newB.digits[i] = 0;
		}
		for (int i = 0; i < b.length; i++){
			newB.digits[i] = b.digits[i];
		}
		for (int ix = 0; ix < (newLength); ix++) // проход по всем разрядам числа, начиная с последнего, не доходя до первого
		{
			if (ix < (newLength - 1)) // если текущий разряд чисел не первый
			{
				digits[ix + 1]--; // в следующуем разряде большего числа занимаем 1.
				result.digits[ix] += 10 + digits[ix]; // в ответ записываем сумму значения текущего разряда большего числа и 10-ти
 
			} else	// если текущий разряд чисел - первый
				result.digits[ix] += digits[ix]; // в ответ суммируем значение текущего разряда большего числа
 
			result.digits[ix] -= newB.digits[ix]; // вычитаем значение текущего разряда меньшего числа
 
			if (result.digits[ix] / 10 > 0) // если значение в текущем разряде двухразрядное
			{
				result.digits[ix + 1]++; // переносим единицу в старший разряд
				result.digits[ix] %= 10; // в текущем разряде отсекаем ее
			}
		}
			
		while (result.digits[result.length - 1] == 0)
			--result.length;
		if (result.length == 0){
			result.length = 1;
			result.digits[0] = 0;
		}

		return result;
	}
	//-------------------------------------------------------*Оператор - -------------------------------------------------------------------------//	

	//-------------------------------------------------------*Оператор * -------------------------------------------------------------------------//
	hugeInt operator*(hugeInt b){
	
		int newLength = length + b.length + 1;
		hugeInt result(newLength);
		hugeInt newB(newLength);
		for (int i = 0; i < newLength; i++){
			result.digits[i] = 0;
			newB.digits[i] = 0;
		}
		for (int i = 0; i < b.length; i++)
			newB.digits[i] = b.digits[i];


		for (int i=0;i<length;i++)
		{
			int r = 0;
			for (int j=0;j<b.length | r;j++)
			{
				result.digits[i+j] += digits[i] * newB.digits[j] + r;
				r = result.digits[i+j] / 10;
				result.digits[i+j] -= r * 10;
			}
		}
		while (result.digits[result.length - 1] == 0)
			--result.length;
		if (result.length == 0){
			result.length = 1;
			result.digits[0] = 0;
		}

		return result;
	}
	//-------------------------------------------------------*Оператор * -------------------------------------------------------------------------//

	//-------------------------------------------------------*Оператор * на int -------------------------------------------------------------------------//
	/*hugeInt operator * (int b){
	}*/

	//-------------------------------------------------------*Оператор * на int -------------------------------------------------------------------------//

	//-------------------------------------------------------*Остаток  от деления -------------------------------------------------------------------------//	
	hugeInt mod(hugeInt a, hugeInt b){
		hugeInt a1(b.length);
		hugeInt c(1);
		hugeInt result(1);
		
		if (a < b)
			return a;
		do{
			a1.length = b.length;
			for (int i = 0; i < a1.length; i++)
				a1.digits[i] = 0;

		//Выбираем из A слева столько цифр, сколько их в B. Получаем число A1.
		for (int i = 0; i < b.length; i++) 
			a1.digits[a1.length - i - 1] = a.digits[a.length - i - 1];
		//Если А1 меньше чем B, то прибавляем в него еще одну цифру из А.
		if (a1 < b){
			a1.length = b.length + 1;
			for (int i = a1.length - 1; i > 0 ; i--)
				a1.digits[i] = a1.digits[i-1];
			a1.digits[0] = a.digits[a.length - b.length - 1];
		}
		if (a1.digits[a1.length - 1] == 0)
			--a1.length;
		//Перебором всех цифр С находим самую большую, при которой "элементарное произведение" C*B <= A1
		for (int i = 0; i < 9; i++){
			c = i;
			if (c * b > a1){
				c = i - 1;
				break;
			}
			if (c * b == a1)
				break;
		}
		// Если A >= B Повторяем , иначе деление закончено и A - остаток от деления
		a = a - c * b;
		
		} while (a >= b);
		return a;
	}
	//-------------------------------------------------------*Остаток от деления -------------------------------------------------------------------------//	

	//-------------------------------------------------------*Ввод-------------------------------------------------------------------------------//	
	void input(){
		std::string s;
		std::cin>>s;
		length = s.length();
		digits = new short[length];
		for (int i = 0; i < s.length(); i++){
			digits[i] = s[length - i - 1] - '0';
		}
	}
	//-------------------------------------------------------*Ввод-------------------------------------------------------------------------------//

	//-------------------------------------------------------*Возведение в степень по модулю----------------------------------------------------//	
	hugeInt powerMod(hugeInt b, int e, hugeInt m){
		hugeInt c(m.length);
		c = 1;
		/*hugeInt i(1);
		hugeInt iteration(1);
		iteration = 1;
		hugeInt test("4");
		c = c.mod(test,m);
		*/
		for (int i = 1; i <= e; i++){
			c = c.mod((c*b), m);
		}
		return c;
	}
	//-------------------------------------------------------*Возведение в степень по модулю-----------------------------------------------------//	

	//-------------------------------------------------------*Проверка на четность----------------------------------------------------//	
	bool prime(){
		if (digits[0] % 2 == 0)
			return true;
		return false;
	}
	//-------------------------------------------------------*Проверка на четность----------------------------------------------------//	
};


int _tmain(int argc, _TCHAR* argv[])
{
	hugeInt first(500);
	first.random(500);
	hugeInt second("497");
	hugeInt m(0);
	
	first.print();
	second.print();
	/*m = m.mod(first, second);
	m.print();*/
	/*m = first.powerMod(first,13, second);
	m.print();*/
	bool a = first.prime();
	std::cout<<a<<std::endl;
	system("pause");
	return 0;
}

