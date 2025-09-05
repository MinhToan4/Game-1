#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "Animation.hpp"
#include "level.hpp"
#include <fstream>
#include<sstream>
using namespace std;
class Result{
	public:
		int fre=1; // check state
		sf::Sprite sprite;
		int maxresult=0;
		void writescore(int n); // write score to file
		void getmax();
		void Draw1(sf::RenderWindow &window,string imagepath,float x,float y);
		void Draw2(sf::RenderWindow &window,float x,float y);
};
void Result::Draw1(sf::RenderWindow &window,string imagepath,float x,float y){
	sf::Image img;
	img.loadFromFile(imagepath);
	// img.createMaskFromColor(sf::Color(255,255,255));
	sf::Texture texture;
	texture.loadFromImage(img); // load image into texture
	sprite.setTexture(texture); // assign texture to sprite
	sprite.setPosition(x,y);
	sprite.setScale(0.4,0.4);
	window.draw(sprite);
}
void Result::Draw2(sf::RenderWindow &window,float x,float y){
	stringstream ss;
	sf::Text a; // create text object to display score
	sf::Font font;
	ss << maxresult; // cpnvert highest score to a string
	font.loadFromFile("files/arial.ttf");
	a.setFont(font);
	a.setColor(sf::Color::White);
	a.setString(ss.str().c_str()); // set score string for text object
	a.setPosition(x,y);
	window.draw(a);
}

// open file and write score to file
void Result::writescore(int n)
{
	ofstream save("files/result.txt",ios_base::app);
	save << n << endl;
	save.close();
}

void Result::getmax(){
	ifstream save;
	save.open("files/result.txt");
	string line;
	//get all score at all line
	while (getline(save,line)){
		string numm=line;
		int temp=atoi(numm.c_str());
		if (temp > maxresult) maxresult=temp;
	}
	save.close();
}
