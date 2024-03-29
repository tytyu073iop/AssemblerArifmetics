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
	std::cout << "sum unstable:" << pr1 << '\n';
	// nadegno
	_asm {
		mov al,x1
		cbw
		mov pr1,ax
		mov al,y1
		cbw
		add pr1,ax
	}
	std::cout << "sum:" << pr1 << '\n';
	_asm {
		mov al,x1
		imul y1
		mov pr1,ax
	}
	std::cout << "mul:" << pr1 << '\n';
	std::cout << "enter two in word (-32768)\n";
	std::cin >> x2 >> y2;
	_asm {
		mov ax,x2
		imul y2
		mov pr2,ax
		mov pr1,dx //why
	}
	std::cout << "mul word:" << pr2 << " " << pr1 << '\n';
	_asm {
		mov ax, x2
		imul y2
		mov word ptr pr3, ax
		mov word ptr pr3+2, dx
	}
	std::cout << "mul stable:" << pr3 << '\n';
	_asm {
		mov al,20
		imul x1
		mov pr2,ax
	}
	std::cout << "mul 20:" << pr2 << '\n';
	x3 = 50;
	_asm {
		mov eax,x3
		// imul ebx,eax,50 or
		imul ebx,x3,50
		mov pr3,ebx
	}
	std::cout << "mul 50 in ebx:" << pr3 << '\n';
	_asm {
		mov al,x1
		cbw
		idiv y1
		cbw
		mov pr2,ax
		// mov byte ptr pr1, ah or
		// mov al,ah
		// cbw
		// mov pr1,ax - ah clears after cbw
	}
	std::cout << "div byte:" << pr2 << '\n';
	_asm {
		mov ax, x2
		cwd
		idiv y2
		mov pr2,ax
	}
	std::cout << "div short:" << pr2 << '\n';
	y3 = 50;
	_asm {
		mov eax,x3
		cdq
		idiv y3
		mov pr3,eax
	}
	std::cout << "div int:" << pr3 << '\n';
	char a;
	short b;
	int c;
	a = -127;
	b = -32768;
	_asm {
		mov al, a
		cbw
		imul b
		mov word ptr c, ax
		mov word ptr c+2,dx
	}
	std::cout << "mul byte and short:" << c << '\n';
	_asm {
		mov ax,b
		cwde //ax - eax
		mov ebx,eax
		mov al,a
		cbw
		cwde //ax - eax
		imul eax,ebx
		mov c,eax
	}
	std::cout << "mul 2 variant:" << c << '\n';
	return 0;
}