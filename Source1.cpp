//????? ???? ???? ??????? ????? ??????? ??????? ?? ????
// ??? ???? ?????? ?????? ?? ????? ?????? ? ????? ???????
// ???? ? call enemy class ????? ??? ??call ??function ? geenerate ?? enemy ??? ??? ????? ???????
#include <chrono>
#include <thread>

enum hardship{EASY,MEDIUM,HARD};
void randomenemy(const hardship &gamehardship) { //????? ??? ?? ????? ??????? ???? ?? ?????? ????? ??? ?? globa
	//l variable ??? ????? flow ???????? ??????
	if (gamehardship ==EASY) {
		this_thread::sleep_for(chrono::seconds(3));
	}
	else if (gamehardship == MEDIUM) {
		enemy();
	}
	else if(gamehardship == HARD) {
		enemy
	}
	else {

	}

}

int main() {
	randomenemy(HARD);

}