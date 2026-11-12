#pragma once

#include "bidder.hpp"
#include "auctioneer.hpp"
#include <vector>

/*
Auction is the controller that wires up an Auctioneer and a set of Bidders,
then drives one auction from the opening bid to its result.
*/
class Auction {
    Auctioneer auctioneer;

public:
    /*
    Initializes an auction with the bidders who will attend. Registers
    each bidder with this auction's Auctioneer.
    :param bidders: vector of Bidder pointers attending the auction.
    */
    Auction(vector<Bidder *> bidders);

    /*
    Starts the auction for the given item at the given starting price,
    drives it to completion, then prints the result and a per-bidder
    summary.
    :param item: name of the item being auctioned.
    :param start_price: the opening bid.
    */
    void simulate_auction(string item, double start_price);
};
