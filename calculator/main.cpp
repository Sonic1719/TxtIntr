#define _USE_MATH_DEFINES
#include <iostream>
#include <getopt.h>
#include <string>
#include <cmath>

void print_help(){
	std::cout <<"Как пользоваться калькулятором площадей:\n"
		  <<" -o, --operation circle [радиус]  - Расчет площади круга\n"
		  <<" -o, --operation triangle [стор1] [стор2] [стор3]  - Расчет площади треугольника\n"
		  <<"Для отрицательных чисел '--'\n"
		  <<"Пример использования: ./calc -o triangle -- -3 4 5\n";
}

int main (int argc, char *argv[]) {
	int opt;
	std::string operation = "";
	
	if (argc == 1) {
		print_help();
		return 0;
	}

	static struct option long_options[] = {
		{"operation", required_argument, 0, 'o'},
		{0, 0, 0, 0}
	};

	int long_index = 0;
	while ((opt = getopt_long(argc, argv, "+o:", long_options, &long_index)) != -1) {
		switch (opt) {
			case 'o':
				operation = optarg;
				break;
			case ':':
				std::cout <<"Ошибка: флаг операции требует значение (circle или triangle)\n";
				return 1;
			case '?':
				std::cout <<"Ошибка: неизвестный параметр комстроки\n";
				print_help();
				return 1;
		}
	}

	if (operation == "circle") {
		if (argc - optind != 1) {
			std::cout <<"Ошибка: для круга нужен 1 операнд (радиус)\n";
			return 1;
		}
		double r = std::stod(argv[optind]);
		if (r < 0) {
			std::cout <<"Ошибка: радиус не может быть отрицательным\n";
			return 1;
		}
		double square = M_PI *r*r;
		std::cout <<"Площадь круга: "<< square << std::endl;
	}
	else if (operation == "triangle") {
		if (argc - optind != 3) {
			std::cout <<"Ошибка: для треугольника нужно 3 операнда (стороны)\n";
			return 1;
		}
		double a = std::stod(argv[optind]);
		double b = std::stod(argv[optind+1]);
		double c = std::stod(argv[optind+2]);
		if (a < 0 || b < 0 || c < 0) {
			std::cout <<"Ошибка: стороны не могут быть отрицательными\n";
			return 1;
		}
		double p = (a + b + c)/2.0;
		double square = sqrt(p * (p - a) * (p - b) * (p - c));

		if (std::isnan(square) || square <=0) {
			std::cout <<"Ошибка: треугольник с такими сторонами не существует\n";
			return 1;
		}
		std::cout <<"Площадь треугольника: "<< square << std::endl;
	}
	else {
		std::cout <<"Ошибка: неизвестная операция " << operation << "\n";
		print_help();
		return 1;
	}
	
	return 0;
}


