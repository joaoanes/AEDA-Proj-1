#ifndef USERS_H_
#define USERS_H_

#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <cstdlib>
#include "Sale.h"

using std::string;
using std::vector;
using std::cout;
using std::cin;
using std::map;

// Para evitar erros na compilacao
class Sale;
class Item;

// Classes de erro. Faz sentido estarem aqui?
class invalidInput{};
class invalidOption : public invalidInput {};
class wrongPassword {};

class User {
private:
	// Contador para saber qual o proximo User Number
	static int userNumberCounter;
	// Numero de utilizador
	const int userNumber;
	// Nome de ecra do utilizador
	const string username;
	// Nome real do utilizador
	string name;
	// password do utilizador
	string password;
	// E-mail do utilizador
	string email;
	// Numero do telefone do utilizador
	string phoneNumber;
	// Pais do utilizador
	string country;
	// Morada do utilizador
	string address;
	// Booleano que indica se o utilizador esta logged in. Faz sentido, dada a implementacao no ebay.h?
	bool isLoggedIn;

public:
	// Construtor, dado um nome de utilizador e uma password
	User (string usernm, string pw);
	// Construtor de utilizador sem parametros. Nao deve acontecer.
	User () : userNumber (-1) {}
	// Altera a password, mas apenas se fornecer a password actual
	bool setPassword(string oldPW, string newPW);
	// Altera o nome real do utilizador
	void setName(string newName);
	// Altera o e-mail do utilizador
	void setEmail(string newEmail);
	// Altera o numero de telefone do utilizador
	void setPhone(string newNumber);
	// Altera o pais do utilizador
	void setCountry(string newCountry);
	// Altera a morada do utilizador
	void setAddress(string newAddress);
	// Interface que permite o utilizador alterar as suas informacoes
	void setInfo ();
	// Devolve o numero de utilizador
	int getUserNumber() const;
	// Devolve o nome de ecra do utilizador
	string getUsername() const;
	// Devolve o nome real do utilizador
	string getName() const;
	// Devolve a password do utilizador
	string getPassword() const;
	// Devolve o e-mail do utilizador
	string getEmail() const;
	// Devolve o numero de telefone do utilizador
	string getPhone() const;
	// Devolve o pais do utilizador
	string getCountry() const;
	// Devolve a morada do utilizador
	string getAddress() const;
	// Devolve se o utilizador esta logged in ou nao. Faz sentido dada a implementacao no ebay.h?
	bool getLogStatus() const;
	// Faz log in do utilizador, caso seja dada a password correcta
	bool logIn (string pw);
	// Faz log out do utilizador
	bool logOut ();
	// Mostra as ratings. Apenas implementado na classe seller mas necessario?
	virtual void showRatings () = 0;
	// Mostra todas as informacoes do utilizador
	virtual void showUser ();
	// Mostra informacao resumida do utilizador
	virtual void showUserLite ();
	// Devolve o tipo de utilizador - comprador ou vendedor
	virtual string getType() const = 0;
	// Trata do processo de acrescentar uma venda. Apenas implementado na classe seller mas necessario?
	virtual void newSale(Sale & sale) = 0;
	// Trata da gestao da wish list. Apenas implementado na classe buyer mas necessario?
	virtual void manage_wishlist () = 0;
};

class Buyer: public User {
private:
	// Vector de items que o utilizador quer
	vector <Item*> wishList;
public:
	// Construtor, dado um nome de utilizador e uma password
	Buyer (string username, string password);
	// Construtor de utilizador sem parametros. Nao deve acontecer.
	Buyer ();
	// Acrescenta um item a wish list
	void addWish(Item* wish);
	// remove um item da wish list
	void removeWish (string itemName);
	// Devolve se o utilizador quer um item ou nao
	bool wishesItem (Item* wish);
	// Devolve "Comprador"
	string getType() const;
	// Mostra todas as informacoes do utilizador
	void showUser();
	// Mostra informacao resumida do utilizador
	void showUserLite ();
	// Trata do processo de acrescentar uma venda. Apenas implementado na classe seller mas necessario?
	void newSale (Sale & sale) {}
	// Gere a wish list
	void manage_wishlist ();
	// Mostra as ratings. Apenas implementado na classe seller mas necessario?
	void showRatings() {}
};

class Seller: public User {
private:
	// Vector das vendas actuais do utilizador
	vector <Sale*> currentSales;
	// Vector das vendas completas feitas pelo utilizador
	vector <Sale*> completedSales;
	// Vector das avaliacoes do vendedor por parte de outros utilizadores
	vector <string> ratings;

public:
	// Construtor, dado um nome de utilizador e uma password
	Seller (string usernn, string pw);
	// Construtor de utilizador sem parametros. Nao deve acontecer.
	Seller ();
	// Acrescenta uma venda ao vector das vendas actuais
	void newSale(Sale & sale);
	// Passa uma venda do vector de vendas actuais para o de vendas completas
	void completeSale(int SaleNum);
	// Acrescenta uma avaliacao ao vendedor
	void addRating (string rating);
	// Devolve "Vendedor"
	string getType() const;
	// Mostra todas as informacoes do utilizador
	void showUser();
	// Mostra informacao resumida do utilizador
	void showUserLite ();
	// Trata da visualizacao das vendas actuais do utilizador e da escolha de uma
	void chooseSale ();
	// Trata da gestao de uma venda, escolhida com o chooseSale
	void manageSale (int Index);
	// Trata da gestao da wish list. Apenas implementado na classe buyer mas necessario?
	void manage_wishlist () {}
	// Visualiza as avaliacoes do vendedor
	void showRatings ();
};

#endif /* USERS_H_ */