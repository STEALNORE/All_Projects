#include "Main.h"

//------------------------------------------------------------------------------------------------------------
struct SFloat16
{
	struct SFields
	{
		unsigned short Fraction : 10;
		unsigned short Exponent : 5;
		unsigned short Sign : 1;
	};

	union
	{
		SFields Fields;
		unsigned short Value;
	} Inner;

	SFloat16()
	{
		Inner.Value = 0;
	}

	operator float()
	{
		return (float)Convert_To_Double();
	}

	operator double()
	{
		return Convert_To_Double();
	}

private:
	double Convert_To_Double()
	{
		int exponent, power_of_2;
		double result;
		double fraction, exponent_part, sign;

		exponent = (int)(Inner.Fields.Exponent) - 15;

		if (Inner.Fields.Exponent == 0)
			fraction = 0.0;
		else
			fraction = 1.0;

		fraction += double(Inner.Fields.Fraction) / 1024.0;

		if (exponent >= 0)
		{
			power_of_2 = 1 << exponent;
			exponent_part = (double)power_of_2;
		}
		else
		{
			power_of_2 = 1 << -exponent;
			exponent_part = 1.0 / (double)power_of_2;
		}

		if (Inner.Fields.Sign == 0)
			sign = 1.0;
		else
			sign = -1.0;

		result = sign * exponent_part * fraction;

		return result;
	}
};
//------------------------------------------------------------------------------------------------------------
int main(void)
{
	int i;

	//float one_variable = 123.4f;
	//float another_variable = -1.2f;

	//int one_variable = 0;
	//float another_variable = 12345678901.0f;

	int left_ints[] = { 10, 20, 12345, 1234567890 };
	int right_ints[] = { 30, 40, 5, 123 };
	//int result_ints[4] = {};
	long long result_qwords[2] = {};

	double left_doubles[] = { 2.71, 12345678.0 };
	double right_doubles[] = { 567.8, 0.0000009 };
	double result_doubles[2] = {};

	//char left_bytes[] =  "abcdefghабвгдежз";
	//char right_bytes[] = "asdfghjklzxcvbnm";
	//char right_bytes[] = { -1, 0, -1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };
	//char right_bytes[] = { 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3 };
	//char right_bytes[] = "****************";
	char left_bytes[] = { 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160 };
	char right_bytes[] = { 10, 10, 10, 10, 20, 20, 20, 20, 30, 30, 30, 30, 40, 40, 40, 40 };
	//char result_bytes[17] = {};

	short left_values[] = { 10, -10, 0x1234, -0x1234, 1, 2, 3, 4 };
	short right_values[] = { 20, -10, 0x5678, -0x5678, 10, 20, 30, 40 };
	short result_words[8] = {};
	//int result_ints[4] = {};

	float left_singles[] = { 1.0f, 3.14159f, 2.71f, 12345678.0f };
	float right_singles[] = { 1.0f, -1.234f, 567.8f, 0.0000009f };
	float result_singles[4] = {};
	SFloat16 result_fp16[8] = {};

	Test_Command(left_singles, right_singles, result_fp16);

	for (i = 0; i < 4; i++)
		result_singles[i] = result_fp16[i];


	AsCommander Commander;

	if (! Commander.Init() )
		return -1;

	Commander.Run();

	return 0;
}
//------------------------------------------------------------------------------------------------------------
