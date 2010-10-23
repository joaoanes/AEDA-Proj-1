#ifndef ITEM_H_
#define ITEM_H_
#include <string>
#include <vector>
#include <iostream>

using std::string;
using std::vector;
using std::cout;

class Item
{
	// Contador de items para atribuir um item number. Necessario?
	static int items;
	// Da erro parvo quando se declara como const. 
	// Tal como o static, necessario?
	//const
	int itemnumber;
	// Nome do item
	string name;
	// Descricao do item
	string description;
	// Tags do item
	vector<string> tags;
public:
	// Construtor, dado o nome do item
	Item (string name);
	// Construtor sem parametros
	Item ();
	// Resto de uma implementacao anterior?
	int calculatePostage();
	// Devolve a descricao
    string getDescription() const;
	// Devolve o numero do item
    int getItemnumber() const;
	// Devolve o valor do contador de items? Desnecessario imo
    int getItems() const;
	// Devolve o vector de tags? Necessario?
    vector<string> getTags() const;
	// Define a descricao do item
    void setDescription(string descricao);
	// Altera o itemnumber. Desnecessario.
    void setItemnumber(int itemnumber);
	// Acrescenta uma tag ao vector de tags
    void addTag(string tag);
	// Altera o nome
    void setName (string name);
	// Devolve o nome
    string getName ();
	// Mostra informacao resumida
	void showLite();
};

#endif