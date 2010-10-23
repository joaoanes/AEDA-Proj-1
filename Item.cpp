#include "Item.h"

// Inicializacao do membro estatico
int Item::items = 1;

// Construtor, dado o nome do item
Item::Item (string name) : itemnumber (items) {
	setName (name);
	++items;
}

// Construtor sem parametros
Item::Item () : itemnumber(items) {
	++items;
}

// Devolve a descricao
string Item::getDescription() const
{
    return description;
}

// Devolve o numero do item
int Item::getItemnumber() const
{
    return itemnumber;
}

// Devolve o valor do contador de items? Desnecessario imo
int Item::getItems() const
{
    return Item::items;
}

// Devolve o vector de tags? Necessario?
vector<string> Item::getTags() const
{
    return tags;
}

// Define a descricao do item
void Item::setDescription(string description)
{
    this->description = description;
}

// Acrescenta uma tag ao vector de tags
void Item::addTag(string tag)
{
    tags.push_back (tag);
}

// Devolve o nome
string Item::getName () {
	return name;
}

// Altera o nome
void Item::setName (string name) {
	this->name = name;
}

// Mostra informacao resumida
void Item::showLite() {
	cout << getName() << "\n" << getDescription() << "\nTags: ";
	unsigned i;
	// Mostra as tags, uma a uma ate mostrar 5 ou todas
	for (i = 0; i < tags.size() && i < 5; ++i)
		cout << tags [i] << " ";
	// Caso nao tenha mostrado tas as tags do vector, reticencias para indicar que ha mais
	if (i != tags.size())
		cout << "...";
}