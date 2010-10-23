#ifndef SALE_H_
#define SALE_H_
#include "Users.h"
#include "Item.h"
#include "Date.h"

// Evitar erros na compilacao
class User;
class Buyer;
class Seller;


class Sale {
private:
	// Contador que indica o proximo sale number a atribuir
	static int saleCounter;
	// Indica o numero especifico da sale
	const int saleNo;
	// Titulo da sale
	string title;
	// Item a ser vendido.
	Item _item;
	// Apontador para o vendedor
	Seller* seller;
	// Data de inicio. Necessario? Se bem que o enunciado sugere que sim
	Date startDate;
	// Custo de envio. Necessario?
	double shippingFee;
	// Descricao da sale.
	string description;
public:
	// Construtor que reebe uma data de parametros. Pouco practico
	Sale(int n_sale, string _title,Item sale_item, Seller* _seller, Date date, double fee, string descrip);
	// Construtor sem parametros
	Sale ();
	// Funcao que recebe informacao do utilizador relativa a sale. Virtual, pois varia consoante o tipo de sale
	virtual void saleSetUp ();
	// Devolve o contador que indica o sale number a atribuir. Necessario?
	int getSaleCounter();
	// Altera o SaleCounter. Desnecessario
	void setSaleCounter();
	// Devolve a descricao da sale
    string getDescription() const;
	// Devolve o item a ser vendido. TODO: Alterar para devolver um apontador
    Item getItem() const;
	// Devolve o numero da sale.
    int getSaleNo() const;
	// Devolve o apontador para o vendedor
    Seller* getSeller() const;
	// Devolve o custo de envio. Necessario?
    double getShippingFee() const;
	// Devolve a data de inicio? Necessario de implementar?
    Date getStartDate() const;
	// Devolve o titulo da venda
    string getTitle() const;
	// Altera a descricao da venda
    void setDescription(string description);
	// Altera o item a ser vendido. Necessario?
    void setItem(Item _item);
	// Altera o sale number. Desnecessario.
    void setSaleNo(int saleNo);
	// Altera o custo de envio. Necessario?
    void setShippingFee(double shippingFee);
	// Altera o titulo da venda
    void setTitle(string title);
	// Mostra toda a informacao da venda
    virtual void showSale ();
	// Mostra informacao resumida da venda
	void ShowSaleLite();
	// Devolve o tipo de venda
    virtual string getType() = 0;
	// Serializa para um ficheiro
	virtual bool serialize();
};



class Auction: public Sale
{
private:
	// Data de terminacao do leilao. Necessario implementar?
	Date EndDate;
	// Valor minimo da proxima licitacao
	double minimumBid;
	// Valor que termina a venda e faz com que o utilizador ganhe
	// automaticamente o leilao. PROBLEMA: e se o vendedor nao quiser
	// defenir valor de buyItNow?
	double buyItNow;
	// Apontador para o utilizador que fez a ultima licitacao.
	Buyer* lastBidder;

public:
	// Construtor com mais que muitos parametros. Pouco practico neste momento.
	Auction(int n_sale, string _title,Item sale_item, Seller* _seller, Date date, double fee, string descrip,
			Date end_date, double min_bid, double buy_now, Buyer* last_bidder);
	// Construtor sem parametros
	Auction () : Sale () {}
	// Devolve o valor de buy it now
    double getBuyItNow() const;
	// Devolve a data de terminacao
    Date getEndDate() const;
	// Devolve apontador para o utilizador que fez a ultima licitacao
    Buyer* getLastBidder() const;
	// Devolve o valor minimo da proxima licitacao
    double getMinimumBid() const;
	// Altera o valor de buy it now. Faz sentido ser alteravel?
    void setBuyItNow(double buyItNow);
	// Altera a data de terminacao. Faz sentido ser alteravel?
    void setEndDate(Date EndDate);
	// Altera o utilizador que fez a ultima licitacao
    void setLastBidder(Buyer* lastBidder);
	// Altera o valor minimo da proxima licitacao
    void setMinimumBid(double minimumBid);
	// Mostra toda a informacao da venda
    void showSale ();
	// Devolve "Leilao"
    string getType();
	// Lida com as informacoes do leilao, atraves de inputs do utilizador
    void saleSetUp ();
};

class Advertisement : public Sale
{
public:
	// Construtor com varios parametros. Pouco practico.
	Advertisement(int n_sale, string _title,Item sale_item, Seller* _seller, Date date, string descrip);
	// Construtor sem parametros
	Advertisement () : Sale () {}
	// Mostra toda a informacao da venda
	void showSale();
	// Devolve "Anuncio"
	string getType();
	// Lida com as informacoes do leilao, atraves de inputs do utilizador
	void saleSetUp ();
};

class DirectSale : public Sale
{
private:
	// Preco do item a ser vendido
	double price;
public:
	// Construtor com varios parametros. Pouco practico.
	DirectSale(int n_sale, string _title,Item sale_item, Seller* _seller, Date date, double fee, string descrip, double _price);
	// Construtor sem parametros
	DirectSale () : Sale () {}
	// Devolve o preco do item
	double getPrice();
	// Altera o preco do item
	void setPrice(double _price);
	// Mostra toda a informacao da venda
	void showSale ();
	// Devolve "Venda"
	string getType();
	// Lida com as informacoes do leilao, atraves de inputs do utilizador
	void saleSetUp ();
};

#endif
