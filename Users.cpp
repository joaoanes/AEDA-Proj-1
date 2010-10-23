/*
 * Users.c
 *
 *  Created on: 2 de Out de 2010
 *      Author: João
 */

#include "Users.h"

// Inicializacao do membro estatico
int User::userNumberCounter = 1;

// Construtor, dado um nome de utilizador e uma password
User::User (string usernm, string pw) : userNumber (userNumberCounter), username(usernm){
	password = pw;
	userNumberCounter++;
}

// Altera a password, mas apenas se fornecer a password actual
bool User::setPassword(string oldPW, string newPW) {
	if (oldPW != getPassword())
		return false;
	password = newPW;
	return true;
}

// Altera o nome real do utilizador
void User::setName (string newName) {
	name = newName;
}

// Altera o e-mail do utilizador
void User::setEmail (string newEmail) {
	email = newEmail;
}

// Altera o numero de telefone do utilizador
void User::setPhone (string newNumber) {
	phoneNumber = newNumber;
}

// Altera o pais do utilizador
void User::setCountry (string newCountry) {
	country = newCountry;
}

// Altera a morada do utilizador
void User::setAddress (string newAddress) {
	address = newAddress;
}

// Interface que permite o utilizador alterar as suas informacoes
void User::setInfo () {
	// TODO: nomes de jeito para as variaveis
	cout << "Escolha a informacao a alterar: \n1 - Password\n2 - Nome\n3 - E-mail\n4 - Numero de Telefone" <<
			"\n5 - Pais\n6 - Morada\n0 - Sair\n";
	string option, miteBeNeeded1, miteBeNeeded2;
	try {
		getline (cin,option);
		if (option.size() != 1 || option[0] < '0' || option[0] > '6')
			throw invalidOption();
		// Alterar password
		if (option[0] == '1') {
			cout << "Escreva a password antiga: ";
			getline (cin, miteBeNeeded1);
			cout << "Escreva a nova password";
			getline (cin, miteBeNeeded2);
			if (!setPassword(miteBeNeeded1, miteBeNeeded2))
				throw wrongPassword();
		}
		// Alterar nome real
		if (option[0] == '2') {
			cout << "Escreva o seu novo nome: ";
			getline (cin, miteBeNeeded1);
			setName (miteBeNeeded1);
		}
		// Alterer e-mail
		if (option[0] == '3') {
			cout << "Escreve o seu novo e-mail: ";
			getline (cin, miteBeNeeded1);
			setEmail (miteBeNeeded1);
		}
		// Alterar numero de telefone
		if (option[0] == '4') {
			cout << "Escreva o seu novo numero de telefone: ";
			getline (cin, miteBeNeeded1);
			for (unsigned i = 0; i < miteBeNeeded1.size(); i++) {
				if (miteBeNeeded1[i] < '0' || miteBeNeeded1[i] > '9')
					throw invalidInput();
			}
			setPhone (miteBeNeeded1);
		}
		// Alterar pais
		if (option[0] == '5') {
			cout << "Escreva o seu novo pais: ";
			getline (cin, miteBeNeeded1);
			setCountry (miteBeNeeded1);
		}
		// Alterar morada
		if (option[0] == '6') {
			cout << "Escreva a sua nova morada: ";
			getline (cin, miteBeNeeded1);
			setAddress (miteBeNeeded1);
		}
		// Sair
		if (option[0] == '0')
			return;
	}
	catch (invalidOption&) {
		cout << "Opcao invalida!";
	}
	catch (wrongPassword&) {
		cout << "Password errada!";
	}
	catch (invalidInput&) {
		cout << "Input invalido!";
	}
	setInfo();
}

// Devolve o numero de utilizador
int User::getUserNumber() const {
	return userNumber;
}

// Devolve o nome de ecra do utilizador
string User::getUsername() const {
	return username;
}

// Devolve o nome real do utilizador
string User::getName() const {
	return name;
}

// Devolve a password do utilizador
string User::getPassword() const {
	return password;
}

// Devolve o e-mail do utilizador
string User::getEmail() const {
	return email;
}

// Devolve o numero de telefone do utilizador
string User::getPhone() const {
	return phoneNumber;
}

// Devolve o pais do utilizador
string User::getCountry() const {
	return country;
}

// Devolve a morada do utilizador
string User::getAddress() const {
	return address;
}

// Devolve se o utilizador esta logged in ou nao. Faz sentido dada a implementacao no ebay.h?
bool User::getLogStatus() const {
	return isLoggedIn;
}

// Faz log in do utilizador, caso seja dada a password correcta
bool User::logIn(string pw) {
	if (pw != getPassword())
		return false;
	isLoggedIn = true;
	return true;
}

// Faz log out do utilizador
bool User::logOut() {
	if (!getLogStatus())
		return false;
	return true;
}

// Mostra todas as informacoes do utilizador
void User::showUser () {
	cout << "\tPerfil de " << getUsername() << "\n\n";
	cout << "Nome: " << getName() << "\nEmail: " << getEmail() << "\nTelefone: " << getPhone();
	cout << "\nPais: " << getCountry() << "\nMorada: " << getAddress();
}

// Mostra informacao resumida do utilizador
void User::showUserLite() {
	cout << getUsername() << "No: " << getUserNumber() << " " << getUsername();
}

// Construtor, dado um nome de utilizador e uma password
Buyer::Buyer (string username, string password) : User (username, password)
{
}

// Construtor de utilizador sem parametros. Nao deve acontecer.
Buyer::Buyer() : User()
{
}

// Acrescenta um item a wish list
void Buyer::addWish(Item* wish)
{
	if (!wishesItem(wish))
		wishList.push_back(wish);
}

// remove um item da wish list
void Buyer::removeWish (string itemName) {
	for (vector <Item*>::iterator it = wishList.begin(); it != wishList.end(); ++it) {
		if ((*it)->getName() == itemName) {
			wishList.erase (it);
			return;
		}
	}
}

// Devolve se o utilizador quer um item ou nao
bool Buyer::wishesItem(Item* wish)
{
	for (unsigned i = 0; i < wishList.size(); ++i)
		if (wishList[i]->getItemnumber() == wish->getItemnumber())
			return true;
	return false;
}

// Devolve "Comprador"
string Buyer::getType () const {
	return "Comprador";
}

// Mostra todas as informacoes do utilizador
void Buyer::showUser () {
	User::showUser ();
	cout << "\nTamanho da 'Wishlist': " << wishList.size();
}

// Mostra informacao resumida do utilizador
void Buyer::showUserLite () {
	cout << getType() << " ";
	User::showUserLite();
}

// Construtor, dado um nome de utilizador e uma password
Seller::Seller (string usernm, string pw) : User (usernm, pw) {}

// Construtor de utilizador sem parametros. Nao deve acontecer.
Seller::Seller() : User()
{
}

// Acrescenta uma venda ao vector das vendas actuais
void Seller:: newSale (Sale & sale) {
	Sale* newSale = &sale;
	currentSales.push_back (newSale);
}

// Passa uma venda do vector de vendas actuais para o de vendas completas
void Seller:: completeSale (int SaleNum) {
	for (vector <Sale*>::iterator it = currentSales.begin(); it != currentSales.end(); ++it) {
		if ((*it)->getSaleNo() == SaleNum) {
			completedSales.push_back (*it);
			currentSales.erase (it);
			return;
		}
	}
}

// Devolve "Vendedor"
string Seller::getType () const {
	return "Vendedor";
}

// Acrescenta uma avaliacao ao vendedor
void Seller::addRating (string rating) {
	ratings.push_back(rating);
}

// Mostra todas as informacoes do utilizador
void Seller::showUser () {
	User::showUser();
	cout << "\nNumero total de vendas: " << (currentSales.size() + completedSales.size());
	cout << "\nNumero de vendas actuais: " << currentSales.size() << "\nNumero de vendas completas: " << completedSales.size();
	cout << "\nNumero de 'ratings': " << ratings.size();
}

// Mostra informacao resumida do utilizador
void Seller::showUserLite() {
	cout << getType() << " ";
	User::showUserLite();
}

// Trata da visualizacao das vendas actuais do utilizador e da escolha de uma
void Seller::chooseSale () {
	string input;
	int inputNum;
	for (unsigned i = 0; i < currentSales.size(); ++i) {
		cout << (i+1);
		currentSales[i]->ShowSaleLite();
		cout << "\n";
	}
	cout << "0 - Sair\n";
	cout << "Que sale deseja gerir?";
	// Validacao do input etc
	try {
		getline (cin, input);
		for (unsigned i = 0; i < input.size(); ++i)
			if (input[i]<'0' || input[i]>'9')
				throw invalidInput();
		inputNum = atoi (input.c_str());
		if (inputNum == 0)
			return;
		if (inputNum < 1 || inputNum > currentSales.size())
			throw invalidOption();
		manageSale (inputNum - 1);
	}
	catch (invalidInput&) {
		cout << "Input ou opcao invalido. Quer voltar a tentar? Y/N";
		getline (cin, input);
		if (input == "Y" || input == "y")
			chooseSale();
	}
}

// Trata da gestao de uma venda, escolhida com o chooseSale
void Seller::manageSale (int Index) {
	string input;
	currentSales[Index]->showSale();
	cout << "O que deseja fazer?\n1 - Alterar titulo\n2 - Alterar descricao\n3 - Terminar venda\n0 - Sair";
	try {
		getline (cin, input);
		// Sair
		if (input == "0")
			return;
		// Alterar titulo
		if (input == "1") {
			cout << "Digite o novo titulo ou pressione enter para sair\n";
			getline (cin, input);
			if (input == "")
				return;
			currentSales[Index]->setTitle(input);
		}
		// Alterar descricao
		if (input == "2") {
			string newDesc;
			cout << "Digite a sua nova descricao. Quando quiser sair pressione apenas Enter.\n";
			while (input != "") {
				getline (cin, input);
				newDesc += input;
			}
			// Se o utilizador tiver apenas pressionado enter e mais nada, sai.
			if (newDesc != "")
				currentSales[Index]->setDescription (newDesc);
		}
		// Terminar venda
		if (input == "3") {
			cout << "Digite Y se tiver a certeza que pertende terminar a venda. Este processo nao pode ser revertido. ";
			// Melhorar o handling deste input?
			getline (cin, input);
			if (input == "Y")
				completeSale (currentSales[Index]->getSaleNo());
		}
		if (input.size() != 1 || input[0] < 0 || input[0] > 3)
			throw invalidInput();
	}
	catch (invalidInput&) {
		cout << "Input invalido. Digite Y se quiser tentar outra vez";
		getline (cin, input);
		if (input == "Y")
			manageSale (Index);
	}
}

// Gere a wish list
void Buyer::manage_wishlist() {
	string input;
	for (unsigned i = 0; i < wishList.size(); ++i) {
		cout << (i+1) << " - ";
		wishList [i] -> showLite ();
	}
	cout << "O que deseja fazer? \n1 - Remover item\n0 - Sair";
	// Tratamento de inputs etc
	try {
		getline (cin, input);
		if (input.size() != 1)
			throw invalidInput();
		if (input[0] < '0' || input[0] > '1')
			throw invalidOption();
		if (input == "1") {
			cout << "Qual o numero do item que deseja remover? ";
			getline (cin,input);
			for (unsigned i = 0; i < input.size(); ++i)
				if (input[i]<'0' || input[i]>'9')
					throw invalidInput();
			int inputNum = atoi (input.c_str());
			vector<Item*>::iterator it = wishList.begin();
			for (int i = 0; i < inputNum; ++i)
				++it;
			wishList.erase (it);
		}
		if (input == "0")
			return;
	}
	catch (invalidOption &) {
		cout << "Opcao invalida, a voltar para o menu principal...\n";
	}
	catch (invalidInput &) {
		cout << "Input invalido, a voltar para o menu principal...\n";
	}
}

// Visualiza as avaliacoes do vendedor
void Seller::showRatings () {
	for (unsigned i = 0; i < ratings.size(); ++i)
		cout << i << " - " << ratings[i];
}