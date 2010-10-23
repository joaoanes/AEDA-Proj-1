#ifndef EBAY_H_
#define EBAY_H_

#include <string>
#include <vector>
#include "Sale.h"
#include "Frame.h"

using namespace std;

class CppBay{
private:
	// vector de utilizadores
	vector<User*> users;
	// resto de uma abordagem anterior
	//vector<User*> logged_users;
	// apontador para o user que esta logged in
	User* logged_user;
	// vector de sales
	vector<Sale*> sales;
public:
	// classe de erro
	class NonExistingUser {};
	// Construtor que recebe os vectores. Valera a pena, visto que o loading e um membro funcao da classe?
	CppBay(vector<User*> users,vector<Sale*> sales);
	// Construtor sem parametros
	CppBay ();
	// resto de uma abordagem anterior
	//bool isLoggedIn(string username);
	// Funcao que faz log in de um utilizador
	void Log_In(string username,string password);
	// Funcao que faz log out do utilizador actual
	void Log_out ();
	// Push back do vector de utilizadores
	void addNewUser(User* user);
	// Push back do vector de sales
	void addNewSale(Sale* sale);
	// Funcao que elimina um utilizador. Valera a pena?
	bool removeUser(string username, string password);
	// Mostra todas as sales, nao com informacao completa
	void showSales();
	// Mostra todos os utilizadores, nao com informacao completa
	void showUsers();
	// Main menu para quando nao se esta logged in
	void mainMenu ();
	// Main menu, para quando se esta logged in como vendedor
	void mainMenuSeller ();
	// Menu principal, quando se esta logged in como buyer
	void mainMenuBuyer ();
	// Funcoes de procura de utilizadores conforme determinados criterios.
	// Havera maneira de evitar redundancia?
	vector <User*> searchByCountry(string country);
	vector <User*> searchByEmail (string email);
	vector <User*> searchByUsername (string username);
	vector <User*> searchByName (string name);
	//TODO: procura sales, dadas tags de items. String com a tag ou vector de tags?
	vector <Sale*> searchItemByTags ();
	//TODO: procura sales, dado nome de item
	vector <Sale*> searchItemByName (string name);
	//TODO: Um bocado feito. Precisamos de decidir como fazer o searchItemByTags
	void browser();
	//Regista um utilizador. Ver comentarios no cpp.
	void register_user();
	// TODO: ainda nao fazemos ideia de como organizar a informacao guardada
	void save_data ();
	//TODO: mesma situacao que save
	void load_data();
	//TODO: ver cpp
	void select_and_show_user (vector<User*> searchedUsers);
	//TODO: interacçao com os resultados de uma pesquisa de items/sales
	void select_and_show_item (vector <Sale*> searchedSales);
};

#endif /* EBAY_H_ */
