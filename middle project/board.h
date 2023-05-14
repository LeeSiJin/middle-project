#include <fstream>
#include <vector>
#include "page.h"

using namespace std;
using std::endl;
using std::ofstream;

class Board {
public:
	Board(int num_jobs, int width, int height, ofstream& output_stream);
	~Board();

	void print_board();
	void print_job(int job_idx, char job_type, int id);

	//job functions
	void insert_page(int x, int y, int width, int height, int id, int content);
	void insert_page(Page& newpage);
	void delete_page(int id);
	void modify_content(int id, char content);
	void modify_position(int id, int x, int y);


private:
	int num_jobs, width, height;
	ofstream& output;
	char* board;
	Page getPageById(int id);
	Page getPageByContent(char content);
};


//page 저장할 page array
vector<Page> page_array;


Page getPageByContent(char content) {
	for (int i = 0; i < page_array.size(); i++)
	{
		if (page_array[i].getreturncontent() == content) {
			return page_array[i];
		}
	}
}

Page Board::getPageById(int id) {
	for (int i = 0; i < page_array.size(); i++)
	{
		if (page_array[i].getreturnid() == id) {
			return page_array[i];
		}
	}
}

Board::Board(int num_jobs, int width, int height, ofstream& output_stream) : output(output_stream) {
	this->width = width;
	this->height = height;
	this->num_jobs = num_jobs;

	board = new char[width * height];

	for (int h = 0; h < height; h++) {
		for (int w = 0; w < width; w++) {
			board[h * width + w] = ' ';
		}
	}

}

Board::~Board() {
	delete board;

}


void Board::print_board() {
	int h, w;
	for (w = 0; w < width + 2; w++) output << "- ";
	output << endl;

	for (h = 0; h < height; h++) {
		output << "| ";
		for (w = 0; w < width; w++) {
			output << board[h * width + w] << " ";
		}
		output << "| " << endl;
	}

	for (w = 0; w < width + 2; w++) output << "- ";
	output << endl;
}

void Board::print_job(int job_idx, char job_type, int id) {
	output << ">> (" << job_idx << ") ";
	switch (job_type) {

	case 'i':
		output << "Insert ";
		break;
	case 'd':
		output << "Delete ";
		break;
	case 'm':
		output << "Modify ";
		break;
	}

	output << id << endl;
}

bool check_conflict(int x, int y, int z, int k, int a, int b, int c, int d) {
	int leftup_a[2] = { y, x };
	int rightup_a[2] = { y,x + z };
	int leftdown_a[2] = { y + k,x };
	int rightdown_a[2] = { y + k,x + z };

	int leftup_b[2] = { b,a };
	int rightup_b[2] = { b, a + c };
	int leftdown_b[2] = { b + d, a };
	int rightdown_b[2] = { b + d,a + c };


	if (a + c<x || a>x + z || b > y + k || b + d < y) {
		return true;
	}

}



void Board::insert_page(int x, int y, int width, int height, int id, int content) {
	Page newpage(x, y, width, height, id, content); //page만들기    

	//충돌이 난 경우 conflict page에 기록
	for (int i = 0; i < page_array.size(); i++)
	{
		// check 함수를 통해 겹치는 지 확인
		if (check_conflict(page_array[i].getReturnX(), page_array[i].getreturny(), page_array[i].getreturnwidth(), page_array[i].getreturnheight(), x, y, width, height == true)) {
			// 겹치는 결과 반영
			newpage.input_conflict_page(page_array[i].getreturnid());
		}

	}

	//보드에 내용 넣어주기
	for (int h = y; h < y + height; h++) {
		for (int w = x; w < x + width; w++) {
			if (h < this->height && w < this->width) {

				board[h * this->width + w] = content;
			}
		}
	}
	page_array.push_back(newpage);
	/*page_array[page_counter++] = newpage;*/
	print_board();
}
void Board::insert_page(Page & newpage) {   
	int x = newpage.getReturnX();
	int y = newpage.getreturny();
	int height = newpage.getreturnheight();
	int width = newpage.getreturnwidth();
	char content = newpage.getreturncontent();
	int index;
	newpage.get_conflictpage().clear();
	for (int i = 0; i < page_array.size(); i++)
	{
		if (newpage.getreturnid() == page_array[i].getreturnid())
		{
			index = i;
			break;
		}
	}
	

	//충돌이 난 경우 conflict page에 기록
	for (int i = 0; i < index; i++)
	{
		// check 함수를 통해 겹치는 지 확인
		if (check_conflict(page_array[i].getReturnX(), page_array[i].getreturny(), page_array[i].getreturnwidth(), page_array[i].getreturnheight(), x, y, width, height == true)) {
			// 겹치는 결과 반영
			newpage.input_conflict_page(page_array[i].getreturnid());
		}

	}
	//보드에 내용 넣어주기
	for (int h = y; h < y + height; h++) {
		for (int w = x; w < x + width; w++) {
			if (h < this->height && w < this->width) {

				board[h * this->width + w] = content;
			}
		}
	}

	print_board();
}

void Board::delete_page(int id) {
	Page page = getPageById(id);
	//가져온 페이지 정보
	int currentX = page.getReturnX();
	int currentY = page.getreturny();
	int width = page.getreturnwidth();
	int height = page.getreturnheight();

	//겹치는 페이지들 삭제 - by 재귀
	/*for (int h = currentY; h < currentY + height; h++) {
		for (int w = currentX; w < currentX + width; w++) {
			if (board[h * this->width + w] != ' ') {
				int currentPageId = getPageByContent(board[h * this->width + w]).getreturnid();
				if (currentPageId != id) {
					delete_page(currentPageId);
				}
			}
		}
	}*/
	int index; // 3th inserted - 땔려고 하는 목표 페이지
	for (int i = 0; i < page_array.size(); i++)
	{
		if (page.getreturnid() == page_array[i].getreturnid())
		{
			index = i;
			break;
		}
	}
	vector<Page> conflictAll;
	conflictAll.push_back(page);

	for (int i = index + 1; i < page_array.size(); i++)
	{
		//만약에 i번째 page가 conflictAll에 있는 페이지와 충돌한다?
		page_array[i];
		// => true / conflictAll에 i번째 page를 추가해준다.
		bool t = false;

		for (int j = 0; j < conflictAll.size(); j++)
		{
			for (int w = 0; w < page_array[i].get_conflictpage().size(); w++)
			{
				if (conflictAll[j].getreturnid() == page_array[i].get_conflictpage()[w]) {
					t = true;
				}

			}
		}




		if (t == true)
		{
			
			conflictAll.push_back(page_array[i]);
		}

	}
	// conflictAll에 있는 친구들을 다 때주면 된다.
	for (int i = conflictAll.size() - 1; i >= 0; i--)
	{
		

		// 지운 페이지 밑에 어떤 content가 있는지를 알아야. 화면을 출력함.
		// 1. 지우려는 페이지 A의 영역을 모두 순회한다.
		// 2. 한 좌표(x, y)에 대해서 겹치는 A 페이지의 conflict_page가 있는지 역순으로 확인한다.
		// 3. 겹치는 페이지가 있으면 해당 좌표의 content를 conflict_page에 해당하는 content로 채운다.
		// 4. 겹치는 페이지가 없으면 ' ' 공백으로 채운다.
		for (int h = conflictAll[i].getreturny(); h < conflictAll[i].getreturny() + conflictAll[i].getreturnheight(); h++) {
			for (int w = conflictAll[i].getReturnX(); w < conflictAll[i].getReturnX() + conflictAll[i].getreturnwidth(); w++) {
				bool isModified = false;
				for (int k = conflictAll[i].get_conflictpage().size() - 1; k >= 0; k--)
				{
					int gx = getPageById(conflictAll[i].get_conflictpage()[k]).getReturnX();
					int gy = getPageById(conflictAll[i].get_conflictpage()[k]).getreturny();
					int gw = getPageById(conflictAll[i].get_conflictpage()[k]).getreturnwidth();
					int gh = getPageById(conflictAll[i].get_conflictpage()[k]).getreturnheight();

					int compare_x = w;
					int compare_y = h;

					if ((compare_x >= gx && compare_x < gx + gw && compare_y >= gy && compare_y < gy + gh)&&!isModified) {
						board[h * this->width + w] = getPageById(conflictAll[i].get_conflictpage()[k]).getreturncontent();
						isModified = true;
						break;
					}
				}
				if (!isModified)
				{
					board[h * this->width + w] = ' ';
				}

			}
		}




		print_board();
	}

	//역으로 다시 붙여주기
	for (int i = 1; i < conflictAll.size(); i++)
	{
		// 말 그대로 board에 채워주기만 한다.
		insert_page(conflictAll[i]);
		
	}

}



void Board::modify_content(int id, char content) {
	Page page = getPageById(id);
	//가져온 페이지 정보
	int currentX = page.getReturnX();
	int currentY = page.getreturny();
	int width = page.getreturnwidth();
	int height = page.getreturnheight();

	//겹치는 페이지들 삭제 - by 재귀
	/*for (int h = currentY; h < currentY + height; h++) {
		for (int w = currentX; w < currentX + width; w++) {
			if (board[h * this->width + w] != ' ') {
				int currentPageId = getPageByContent(board[h * this->width + w]).getreturnid();
				if (currentPageId != id) {
					delete_page(currentPageId);
				}
			}
		}
	}*/
	int index; // 3th inserted - 땔려고 하는 목표 페이지
	for (int i = 0; i < page_array.size(); i++)
	{
		if (page.getreturnid() == page_array[i].getreturnid())
		{
			index = i;
			break;
		}
	}
	vector<Page> conflictAll;
	conflictAll.push_back(page);

	for (int i = index + 1; i < page_array.size(); i++)
	{
		//만약에 i번째 page가 conflictAll에 있는 페이지와 충돌한다?
		page_array[i];
		// => true / conflictAll에 i번째 page를 추가해준다.
		bool t = false;

		for (int j = 0; j < conflictAll.size(); j++)
		{
			for (int w = 0; w < page_array[i].get_conflictpage().size(); w++)
			{
				if (conflictAll[j].getreturnid() == page_array[i].get_conflictpage()[w]) {
					t = true;
				}

			}
		}




		if (t == true)
		{

			conflictAll.push_back(page_array[i]);
		}

	}
	// conflictAll에 있는 친구들을 다 때주면 된다.
	for (int i = conflictAll.size() - 1; i >= 0; i--)
	{


		// 지운 페이지 밑에 어떤 content가 있는지를 알아야. 화면을 출력함.
		// 1. 지우려는 페이지 A의 영역을 모두 순회한다.
		// 2. 한 좌표(x, y)에 대해서 겹치는 A 페이지의 conflict_page가 있는지 역순으로 확인한다.
		// 3. 겹치는 페이지가 있으면 해당 좌표의 content를 conflict_page에 해당하는 content로 채운다.
		// 4. 겹치는 페이지가 없으면 ' ' 공백으로 채운다.
		for (int h = conflictAll[i].getreturny(); h < conflictAll[i].getreturny() + conflictAll[i].getreturnheight(); h++) {
			for (int w = conflictAll[i].getReturnX(); w < conflictAll[i].getReturnX() + conflictAll[i].getreturnwidth(); w++) {
				bool isModified = false;
				for (int k = conflictAll[i].get_conflictpage().size() - 1; k >= 0; k--)
				{
					int gx = getPageById(conflictAll[i].get_conflictpage()[k]).getReturnX();
					int gy = getPageById(conflictAll[i].get_conflictpage()[k]).getreturny();
					int gw = getPageById(conflictAll[i].get_conflictpage()[k]).getreturnwidth();
					int gh = getPageById(conflictAll[i].get_conflictpage()[k]).getreturnheight();

					int compare_x = w;
					int compare_y = h;

					if ((compare_x >= gx && compare_x < gx + gw && compare_y >= gy && compare_y < gy + gh) && !isModified) {
						board[h * this->width + w] = getPageById(conflictAll[i].get_conflictpage()[k]).getreturncontent();
						isModified = true;
						break;
					}
				}
				if (!isModified)
				{
					board[h * this->width + w] = ' ';
				}

			}
		}

		print_board();
	}
	//modify 내용 넣어주기
	page_array[index].setcontent(content);
	insert_page(page_array[index]);



	//역으로 다시 붙여주기
	for (int i = 1; i < conflictAll.size(); i++)
	{
		// 말 그대로 board에 채워주기만 한다.
		insert_page(conflictAll[i]);
	
	}


}
void Board::modify_position(int id, int x, int y) {

	
}

