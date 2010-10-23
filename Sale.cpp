#include "Sale.h"

// Inicializacao do membro estatico
int Sale::saleCounter = 1;

// Construtor que reebe uma data de parametros. Pouco practico
Sale::Sale(int n_sale, string _title,Item sale_item, Seller* _seller, Date date, double fee, string descrip) : saleNo(saleCounter)
{
	++saleCounter;
	setTitle(_title);
	setItem(sale_item);
	seller= _seller;
	startDate= date;
	setShippingFee(fee);
	setDescription(descrip);
}

// Construtor sem parametros
Sale::Sale () : saleNo (saleCounter) {
	++saleCounter;
}

// Funcao que recebe informacao do utilizador relativa a sale. Virtual, pois varia consoante o tipo de sale
void Sale::saleSetUp () {
	string input;
	Item newitem;
	cout << "Escolha um titulo para a sua venda: ";
	getline (cin, input);
	setTitle (input);
	cout << "Indique o nome do item que deseja vender: ";
	getline (cin, input);
	newitem.setName (input);
	cout << "Escreva algumas tags para o item, separadas por 'Enter'(pressione Enter sem digitar nada para terminar): \n";
	while (input != "") {
		getline (cin, input);
		newitem.addTag (input);
	}
	// Para evitar que o programa salte o proximo ciclo a frente
	input = "aaa";
	cout << "Escreva uma descricao para a venda(pressione Enter sem digitar nada para terminar): ";
	string newDescription;
	while (input != "") {
		getline (cin, input);
		newDescription += input;
	}
	setDescription (newDescription);
}

// Variante do saleSetUp para leiloes
void Auction::saleSetUp () {
	// TODO: melhorar o controlo de input
	double inputDouble;
	Sale::saleSetUp ();
	cout << "Insira um preco inicial: ";
	cin >> inputDouble;
	setMinimumBid (inputDouble);
	cout << "Insira um preco maximo: ";
	cin >> inputDouble;
	setBuyItNow (inputDouble);
}

// // Variante do saleSetUp para anuncios
void Advertisement::saleSetUp () {
	Sale::saleSetUp();
}

// Variante do saleSetUp para vendas
void DirectSale::saleSetUp () {
	// TODO: melhorar o controlo de input
	double inputDouble;
	Sale::saleSetUp();
	cout << "Insira um preco: ";
	cin >> inputDouble;
}

// Devolve a descricao da sale
string Sale::getDescription() const
{
    return description;
}

// Devolve o item a ser vendido. TODO: Alterar para devolver um apontador
Item Sale::getItem() const
{
    return _item;
}

// Devolve o numero da sale.
int Sale::getSaleNo() const
{
    return saleNo;
}

// Devolve o apontador para o vendedor
Seller* Sale::getSeller() const
{
    return seller;
}

// Devolve o custo de envio. Necessario?
double Sale::getShippingFee() const
{
    return shippingFee;
}

// Devolve a data de inicio? Necessario de implementar?
Date Sale::getStartDate() const
{
    return startDate;
}

// Devolve o titulo da venda
string Sale::getTitle() const
{
    return title;
}

// Altera a descricao da venda
void Sale::setDescription(string description)
{
    this->description = description;
}

// Altera o item a ser vendido. Necessario?
void Sale::setItem(Item _item)
{
    this->_item = _item;
}

// Altera o custo de envio. Necessario?
void Sale::setShippingFee(double shippingFee)
{
    this->shippingFee = shippingFee;
}

// Altera o titulo da venda
void Sale::setTitle(string title)
{
    this->title = title;
}

// Mostra toda a informacao da venda
void Sale::showSale () {
	// Nao faz output da data
	cout << "\t\t" << getTitle();
	cout << "\nTipo: " << getType();
	cout << "\nVenda numero: " << getSaleNo();
	cout << "\nVendedor: " << seller->getName() << "\nObjecto: " << _item.getName();
	cout << "\nDescricao: \n" << getDescription();
	cout << "Custo de envio: " << getShippingFee();
}

// Mostra informacao resumida da venda
void Sale::ShowSaleLite() {
	cout <<"Tipo: " << getType() << " No: " << getSaleNo() << "\t" << getTitle();
}

// Construtor com mais que muitos parametros. Pouco practico neste momento.
Auction::Auction(int n_sale, string _title,Item sale_item, Seller* _seller, Date date, double fee, string descrip,
		Date end_date, double min_bid, double buy_now, Buyer* last_bidder):
		Sale(n_sale, _title, sale_item,  _seller, date, fee, descrip)
{
	setEndDate(end_date);
	setMinimumBid(min_bid);
	setBuyItNow(buy_now);
	setLastBidder(last_bidder);
}

// Devolve o valor de buy it now
double Auction::getBuyItNow() const
{
    return buyItNow;
}

// Devolve a data de terminacao
Date Auction::getEndDate() const
{
    return EndDate;
}

// Devolve apontador para o utilizador que fez a ultima licitacao
Buyer* Auction::getLastBidder() const
{
    return lastBidder;
}

// Devolve o valor minimo da proxima licitacao
double Auction::getMinimumBid() const
{
    return minimumBid;
}
// Altera o valor de buy it now. Faz sentido ser alteravel?
void Auction::setBuyItNow(double buyItNow)
{
    this->buyItNow = buyItNow;
}

	// Altera a data de terminacao. Faz sentido ser alteravel?
void Auction::setEndDate(Date EndDate)
{
    this->EndDate = EndDate;
}

// Altera o utilizador que fez a ultima licitacao
void Auction::setLastBidder(Buyer* lastBidder)
{
    this->lastBidder = lastBidder;
}

// Altera o valor minimo da proxima licitacao
void Auction::setMinimumBid(double minimumBid)
{
    this->minimumBid = minimumBid;
}

// Devolve o tipo de venda - "Leilao"
string Auction::getType() {
	return "Leilao";
}

// Mostra toda a informacao da venda
void Auction::showSale() {
	Sale::showSale();
	cout << "\nUltima licitacao: " << getMinimumBid() << "\nPor: " << lastBidder->getName();
	cout << "\nPreco maximo: " << getBuyItNow();
}

// Construtor com varios parametros. Pouco practico.
Advertisement::Advertisement(int n_sale, string _title,Item sale_item, Seller* _seller, Date date, string descrip):
		Sale(n_sale,_title,sale_item, _seller, date, 0, descrip) {}

// Mostra toda a informacao da venda
void Advertisement::showSale() {
	Sale::showSale();
}
// Devolve o tipo de venda - "Anuncio
string Advertisement::getType() {
	return "Anuncio";
}

// Construtor com varios parametros. Pouco practico.
DirectSale::DirectSale(int n_sale, string _title,Item sale_item, Seller* _seller, Date date, double fee, string descrip,double _price):
		Sale(n_sale, _title, sale_item,  _seller, date, fee, descrip)
{
	setPrice(_price);
}

// Devolve o preco do item
double DirectSale::getPrice()
{
	return price;
}

// Altera o preco do item
void DirectSale::setPrice(double _price)
{
	price= _price;
}

// Mostra toda a informacao da venda
void DirectSale::showSale() {
	Sale::showSale();
	cout << "\nPreco: " << getPrice();
}

// Devolve o tipo de venda - "Venda"
string DirectSale::getType () {
	return "Venda";
}
