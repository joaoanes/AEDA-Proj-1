#include "Frame.h"
#include <iomanip>
using std::cout;


string Frame::loggedinuser = "None";

//Flags manhosos. Podem ser alterados para o que quisermos, pus nomes estranhos para "acidentalmente" nao provocar danos secundarios.
FrameSetter Frame::clr = FrameSetter(0); //limpa o buffer
FrameSetter Frame::print = FrameSetter(1); //imprime o buffer
FrameSetter Frame::flush = FrameSetter(2); //flusha (as in imprime e limpa) buffer
FrameSetter Frame::pause = FrameSetter(3); // pausa a frame corrente. nao imprime nem nada.



Frame::Frame(void)
{
}


Frame::~Frame(void)
{
}

void Frame::printHeader()
{
	//frame is 80x10 probably I can't remember
	//      "                                                                               "
	*this << " /---                                                   Logged in as:";
	*this << ("|                        __   __                         " + loggedinuser);
	*this << "|        |       |      |  / |  | \\ / ";
	*this << "|     ---+--- ---+---   |--  |__|  |   ";
	*this << " \\---    |       |      |__\\ |  |  | ";
}

void Frame::setLoggedinuser(string in)
{
	loggedinuser = in;
}

string Frame::getLoggedinuser()
{
	return loggedinuser;
}

Frame& Frame::operator<<(FrameSetter in)
{
	if (in == clr)
	{
		buffer.clear();
		return *this;
	}
	if (in == print)
	{
		this->printBuffer();
		return *this;
	}
	if (in == flush)
	{
		this->printBufferC();
		return *this;
	}
	if (in == pause)
	{
		this->pauseFrame();
		return *this;
	}
}

Frame& Frame::operator<<(string in)
{
	//TODO error management
	/*Condicoes de erro:
	 *Falta de espaco no buffer? Qual seria o catch disso?
	 * -- Talvez flushar a forca e fazer frame nova para o resto com um pause pelo meio?
	 *
	 *Mandar para fora uma mensagem de erro? Afinal em teoria os pro ( 8) ) gramadores nao enchem o buffer
	 *por acidente.
	 *... mas pode encher a lista de objectos ...
	*/
	string temp;
	size_t lastfound = 0;

	if (buffer.size() == 17)
		// dividir em varias frames se o buffer receber demasiado? TODO
		{
			throw buffFull(); //de momento nao faz bolha.
		}
	else
	{
		while (in.find('\n') != string::npos) //ele procura por \n's e se os encontrar faz newline a maneira dele
											  //aka meter na linha seguinte do buffer
		{
			buffer.push_back((in.substr(0, in.find('\n'))).substr(0, 78)); //espeta 78 chars da string no buffer
			in = in.substr(in.find('\n')+1); //ah ya, e uma funcao destructiva. in nao e const.
		}
		if (in != "")
			buffer.push_back(in);
	}	
	return *this;
}

void Frame::printBufferC()
//isto imprime um header em ASCII todo brutal e faz flush do buffer
//chamado por Frame << Frame::flush;
{
	cout << std::endl << std::endl <<std::endl << std::endl <<std::endl << std::endl;
	// ^ por acaso era so preciso prai 1 ou 2 endlines, mas ja diziam as casas de banho da feup
	// em portugal devia ser tudo maior
	// Í = 0xCD
	// º = 0xBA
	// funciona, a serio.
	// deixa uma linha no fundo para espetar la uma opcao ou algo assim.
	cout  <<              "ÉÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ»";
	 cout << "º /---                                                   Logged in as:         º";
	 cout << std::left << std::setw(79) << ("º|                        __   __                          " + loggedinuser) << "º";
	 cout << "º|        |       |      |  / |  | \\ /                                         º" ;
	 cout << "º|     ---+--- ---+---   |--  |__|  |                                          º";
	 cout << "º \\---    |       |      |__\\ |  |  |                                          º";
	 cout << "ÌÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ¹";
	for (size_t i = 0; i < 15; ++i)
	{
		if (i < buffer.size())
			cout << 'º' << std::setw(78) << std::left << buffer[i] << "º";
		else
			cout << 'º' << std::setw(79) << std::right << "º";
	}
	buffer.clear();
	cout << "ÈÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ¼";
}

void Frame::printBuffer()
//Printa a frame com um ASCII pipi mas conserva o buffer.
//Chamado por Frame << Frame::print;
{
	cout << std::endl << std::endl <<std::endl << std::endl <<std::endl << std::endl;
	// Í = 0xCD
	// º = 0xBA
	// funciona, a serio.
	// deixa uma linha no fundo para espetar la uma opcao ou algo assim.
	cout  <<              "ÉÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ»";
	 cout << "º /---                                                   Logged in as:         º";
	 cout << std::left << std::setw(79) << ("º|                        __   __                          " + loggedinuser) << "º";
	 cout << "º|        |       |      |  / |  | \\ /                                         º" ;
	 cout << "º|     ---+--- ---+---   |--  |__|  |                                          º";
	 cout << "º \\---    |       |      |__\\ |  |  |                                          º";
	 cout << "ÌÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ¹";
	for (size_t i = 0; i < 15; ++i)
	{
		if (i < buffer.size())
			cout << 'º' << std::setw(78) << std::left << buffer[i] << "º";
		else
			cout << 'º' << std::setw(79) << std::right << "º";
	}
	cout << "ÈÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ¼";
}

void Frame::pauseFrame()
//Nem imaginas que flag chama isto.
{
	char c;
	cout << "Carregue enter para continuar...";
	std::cin.get(&c, 1);
	std::cin.clear();
	if (std::cin.peek() == '\n')
		std::cin.ignore(1000, '\n');
}