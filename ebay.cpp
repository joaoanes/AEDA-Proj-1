#include "ebay.h"

// Construtor que recebe os vectores. Valera a pena, visto que o loading e um membro funcao da classe?
CppBay::CppBay(vector<User*> users,vector<Sale*> sales){
	this->users = users;
	this->sales = sales;
}

// Construtor sem parametros
CppBay::CppBay () {}

// Funcao que faz log in de um utilizador
void CppBay::Log_In(string username, string password){
	int size = users.size();
	for(int i= 0; i<size;++i) {
		if(users[i]->getUsername()==username)
		{
			bool log = users[i]->logIn(password);
			//if(log) logged_users.push_back(users[i]);
			if (!log)
				throw wrongPassword();
			return;
		}
	}
	throw NonExistingUser();
}

/*
bool CppBay::isLoggedIn(string username){
	int size = logged_users.size();
	for(int i = 0; i<size;++i)
		if(logged_users[i]->getUsername()==username)
			return true;
	return false;
}
 */

// Mostra todos os utilizadores, nao com informacao completa
void CppBay::showUsers(){
	int size = users.size();
	for(int i=0; i<size;++i)
	{
		users[i]->showUserLite();
		cout<<endl;
	}
}

// Mostra todas as sales, nao com informacao completa
void CppBay::showSales(){
	int size = sales.size();
	for(int i=0; i<size;++i)
	{
		sales[i]->ShowSaleLite();
		cout<<endl;
	}
}

// Push back do vector de utilizadores
void CppBay::addNewUser(User* user){
	users.push_back(user);
}

// Push back do vector de sales
void CppBay::addNewSale(Sale* sale){
	sales.push_back(sale);
}

// Funcao que elimina um utilizador. Valera a pena?
bool CppBay::removeUser(string username, string password){
	int size = users.size();
	for(int i=0;i<size;++i)
	{
		if(users[i]->getUsername()==username && users[i]->getPassword()==password)
		{
			delete users[i];
			users.erase(users.begin()+i);
			return true;
		}
	}
	return false;
}

// Funcao que lida com o registo de um utilizador
void CppBay::register_user() {
	string input, input2, input3;
	cout << "Escolha o seu username: ";
	getline (cin, input);
	cout << "Escolha a sua password: ";
	getline (cin, input2);
	//TODO: melhorar o handling deste input
	cout << "Deseja ser do tipo buyer ou seller? ";
	getline (cin, input3);
	if (input3 == "buyer") {
		Buyer* userpointer = new Buyer (input, input2);
		addNewUser (userpointer);
	}
	else {
		Seller* userpointer = new Seller (input, input2);
		addNewUser (userpointer);
	}
}

// Main menu para quando nao se esta logged in
void CppBay::mainMenu () {
	string input, input2;
	// Por tudo isto num cout?
	cout << "\t\t Bem-vindo\n\n\n";
	cout << "1 - Navegar\n2 - Fazer LogIn\n3 - Registar utilizador\n\n";
	cout << "O que deseja fazer? ";

	// Bloco para lidar com input etc
	try {
		getline (cin, input);
		if (input.size() != 1)
			throw invalidInput();
		if (input[0] < '1' || input[0] > '3')
			throw invalidOption();
		if (input == "1")
			browser();
		if (input == "2") {
			cout << "\nUsername: ";
			getline (cin, input);
			cout << "Passsword: ";
			getline (cin, input2);
			Log_In (input, input2);
		}
		if (input == "3")
			register_user();
	}
	catch (invalidOption &) {
		cout << "Opcao invalida, a voltar para o menu principal...\n";
	}
	catch (invalidInput &) {
		cout << "Input invalido, a voltar para o menu principal...\n";
	}
	catch (wrongPassword &) {
		cout << "Password invalida, a voltar para o menu principal...\n";
	}
	catch (CppBay::NonExistingUser &) {
		cout << "Utilizador invalido, a voltar para o menu principal...\n";
	}
	mainMenu();
}

// Main menu, para quando se esta logged in como vendedor
void CppBay::mainMenuSeller() {
	string input;
	//Output das opcoes
	cout << "1 - Navegar\n2 - Criar venda\n3 - Gerir as minhas vendas\n4 - Editar informacao\n5 - Ver 'ratings'\n6 - Logout\n";

	// Bloco que lida com o input e as opcoes
	try {
		getline (cin, input);
		if (input.size() != 1)
			throw invalidInput();
		if (input[0] < '1' || input[0] > '6')
			throw invalidOption();
		// Navegar
		if (input == "1")
			browser();
		// Criar venda
		if (input == "2") {
			// Necessario, pois precisamos da informacao de se estamos a criar um Leilao, Anuncio ou venda.
			// Sera que podemos tratar disto na classe sale e depois usar o getType() para saber o que fazer?
			// Nao podemos declarar uma venda por ser abstracta
			cout << "Escolha um tipo de venda (Leilao, Anuncio ou Venda): ";
			getline (cin, input);
			if (input == "Leilao") {
				Auction * newsale = new Auction;
				newsale->saleSetUp ();
				logged_user -> newSale (*newsale);
				sales.push_back (newsale);
			}
			else if (input == "Anuncio") {
				Advertisement * newsale = new Advertisement;
				newsale->saleSetUp ();
				logged_user -> newSale (*newsale);
				sales.push_back (newsale);
			}
			else if (input == "Venda") {
				DirectSale * newsale = new DirectSale;
				newsale->saleSetUp ();
				logged_user -> newSale (*newsale);
				sales.push_back (newsale);
			}
			else
				throw invalidInput();
		}
		//TODO: gerir vendas. Gestao de vendas actuais ja
		// implementado na classe seller, mas e vendas ja concluidas?
		if (input == "3") {
		}
		// Editar informacao
		if (input == "4") {
			logged_user->setInfo();
		}
		// Ver as ratings
		if (input == "5")
			logged_user->showRatings();
		// Fazer logout
		if (input == "6") {
			Log_out();
			mainMenu();
		}
	}
	catch (invalidOption &) {
		cout << "Opcao invalida, a voltar para o menu principal...\n";
	}
	catch (invalidInput &) {
		cout << "Input invalido, a voltar para o menu principal...\n";
	}
	mainMenuSeller();
}

// Funcao que faz log out do utilizador actual
void CppBay::Log_out () {
	int size = users.size();
	// Ciclo que procura o utilizador para fazer log out. Ja temos um apontador para o utilizador logged in
	// numa variavel, vale a pena precorrer o vector? Se nao, qual a alternativa?
	for(int i= 0; i<size;++i)
		if(users[i]->getUsername()==(logged_user->getUsername()))
			users[i]->logOut();
	// Poe o apontador para o utilizador logged in a apontar para um local vazio em memoria
	logged_user = 0;
}

// Menu principal, quando se esta logged in como buyer
void CppBay::mainMenuBuyer () {
	string input;
	// Outoput das opcoes
	cout << "1 - Navegar\n2 - Gerir Wishlist\n3 - Editar informacao\n4 - Logout\n";
	// Bloco que lida com o input e as opecoes escolhidas
	try {
		getline (cin, input);
		if (input.size() != 1)
			throw invalidInput();
		if (input[0] < '1' || input[0] > '4')
			throw invalidOption();
		// Navegar
		if (input == "1")
			browser();
		// Gerir Wishlist
		if (input == "2") {
			logged_user -> manage_wishlist();
		}
		// Editar informacao
		if (input == "3") {
			logged_user -> setInfo();
		}
		// Fazer logout
		if (input == "4") {
			Log_out();
			mainMenu();
		}
	}
	catch (invalidOption &) {
		cout << "Opcao invalida, a voltar para o menu principal...\n";
	}
	catch (invalidInput &) {
		cout << "Input invalido, a voltar para o menu principal...\n";
	}
	mainMenuSeller ();
}

// Funcao que devolve um vector com todos os utilizadores do pais especificado
vector <User*> CppBay::searchByCountry (string country) {
	vector <User*> tempVector;
	for (unsigned i = 0; i < users.size(); ++i)
		if (users[i]->getCountry() == country)
			tempVector.push_back(users[i]);
	return tempVector;
}


// Funcao que devolve um vector com todos os utilizadores com o E-mail especificado
vector <User*> CppBay::searchByEmail (string email) {
	vector <User*> tempVector;
	for (unsigned i = 0; i < users.size(); ++i)
		if (users[i]->getEmail() == email)
			tempVector.push_back(users[i]);
	return tempVector;
}

// Funcao que devolve um vector com todos os utilizadores com o username especificado
vector <User*> CppBay::searchByUsername (string username) {
	vector <User*> tempVector;
	for (unsigned i = 0; i < users.size(); ++i)
		if (users[i]->getUsername() == username)
			tempVector.push_back(users[i]);
	return tempVector;
}

// Funcao que devolve um vector com todos os utilizadores com o nome especificado
vector <User*> CppBay::searchByName (string name) {
	vector <User*> tempVector;
	for (unsigned i = 0; i < users.size(); ++i)
		if (users[i]->getName() == name)
			tempVector.push_back(users[i]);
	return tempVector;
}

// Lida com a escolha de utilizadores no browser. Serve para escolher de todos os utilizadores ou de um grupo previamente pesquisado
void CppBay::select_and_show_user (vector<User*> searchedUsers) {
	string input;
	// Mostra os utilizadores do vector
	for (unsigned i = 0; i < searchedUsers.size(); ++i)
		searchedUsers[i]->showUserLite();
	//Bloco que lida com os inputs e as opcoes (pqp teclado do franjas)
	try {
		getline (cin, input);
		// Verifica se e inteiro nao-negativo
		for (unsigned i = 0; i < input.size(); ++i)
			if (input[i]<'0' || input[i]>'9')
				throw invalidInput();
		int inputNum = atoi (input.c_str());
		if (inputNum < 1 || inputNum > searchedUsers.size())
			throw invalidOption();
		// Todo: o que fazer quando o utilizador escolhe outro? No minimo vai ser algo diferente para buyers e sellers
	}
	catch (invalidOption &) {
		cout << "Opcao invalida, a voltar para o menu principal...\n";
	}
	catch (invalidInput &) {
		cout << "Input invalido, a voltar para o menu principal...\n";
	}
}

// Permite pesquisas segundo varios criteiros
void CppBay::browser () {
	string input;
	cout << "O que deseja procurar?\n1- Utilizadores\n2 - Items\vendas\n0 - Voltar";

	// Handling de input
	try {
		getline (cin, input);
		if (input.size() != 1)
			throw invalidInput();
		if (input[0] < '0' || input[0] > '2')
			throw invalidOption();
		// Utilizadores
		if (input == "1") {
			cout << "Escolha o criterio:\n1 - Username\n2 - Nome real\n3 - Pais\n4 - Email\n0 - Menu principal";
			// Yo dawg I heard you like handling inputs so...
			getline (cin, input);
			if (input.size() != 1)
				throw invalidInput();
			if (input[0] < '0' || input[0] > '4')
				throw invalidOption();
			if (input == "1") {
				cout << "Qual o username? ";
				getline (cin, input);
				searchByUsername (input);
			}
			else if (input == "2") {
				cout << "Qual o nome? ";
				getline (cin, input);
				searchByName (input);
			}
			else if (input == "3") {
				cout << "Qual o pais? ";
				getline (cin, input);
				searchByCountry (input);
			}
			else if (input == "4") {
				cout << "Qual o Email? ";
				getline (cin, input);
				searchByEmail (input);
			}
			else if (input == "0")
				return;
		}
		// Items/vendas
		else if (input == "2") {
			cout << "Escolha o criterio:\n1 - Tags\n2 - Nome \n0 - Menu principal\n";
			// Yo dawg I heard you like handling inputs so...
			getline (cin, input);
			if (input.size() != 1)
				throw invalidInput();
			if (input[0] < '0' || input[0] > '2')
				throw invalidOption();
			if (input == "1") {
				// TODO: ver comentário no header no searchItemByTags
			}
			else if (input == "2") {
				cout << "Qual o nome? ";
				getline (cin, input);
				searchItemByName (input);
			}
			else if (input == "0") {
				return;
			}
		}
		// Voltar
		else if (input == "0")
			return;
	}
	catch (invalidOption &) {
		cout << "Opcao invalida, a voltar para o menu principal...\n";
	}
	catch (invalidInput &) {
		cout << "Input invalido, a voltar para o menu principal...\n";
	}
}
