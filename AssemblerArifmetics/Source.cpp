#include <iostream>

int main() {
	setlocale(LC_ALL, ".1251");
	char x1, y1, y11;
	short pr1;
	short x2, y2, pr2;
	int x3, y3, pr3;
	std::cout << "Enter two numbers in byte(127,-128)\n";
	std::cin >> x2 >> y2;
	x1 = x2;
	y1 = y2;
	// ne nadegno
	_asm {
		mov al,x1
		add al,y1
		cbw
		mov pr1,ax
		// mov pr1, al - length of short are TWO bytes
	}
	std::cout << pr1 << '\n';
	// nadegno
	_asm {
		mov al,x1
		cbw
		mov pr1,ax
		mov al,y1
		cbw
		add pr1,ax
	}
	std::cout << pr1 << '\n';
	_asm {
		mov al,x1
		imul y1
		mov pr1,ax
	}
	std::cout << pr1 << '\n';
	std::cout << "enter two in word (-32768)\n";
	std::cin >> x2 >> y2;
	_asm {
		mov ax,x2
		imul y2
		mov pr2,ax
		mov pr1,dx //why
	}
	std::cout << pr2 << " " << pr1 << '\n';
	_asm {
		mov ax, x2
		imul y2
		mov word ptr pr3, ax
		mov word ptr pr3+2, dx
	}
	std::cout << pr3 << '\n';
	_asm {
		mov al,20
		imul x1
		mov pr2,ax
	}
	std::cout << pr2 << '\n';
	_asm {
		mov eax,x3
		// imul ebx,eax,50 or
		imul ebx,x3,50
		mov pr3,ebx
	}
	std::cout << pr3 << '\n';
}