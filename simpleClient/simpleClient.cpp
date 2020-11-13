#include <iostream>
#include <net.h>

enum class CustomMsgTypes : uint32_t
{
	Fireball,
	MovePlayer
};

int main() {

	net::msg<CustomMsgTypes> message;
	message.header.id = CustomMsgTypes::MovePlayer;

	int a = 1;
	bool b = true;
	float c = 455.554f;

	struct
	{
		double x;
		double y;
	} d[5];

	message << a << b << c << d;

	a = 46;
	b = false;
	c = 9.53f;


	return 0;
}
