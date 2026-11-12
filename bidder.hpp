#pragma once

#include <iostream>

using namespace std;

class Auctioneer; // forward declaration - see Lab-08.pptx on why Bidder and
                   // Auctioneer need to refer to each other, and why #include
                   // can't do that for us here

/*
Bidder is the "observer" in our simplified observer pattern. A Bidder watches
an Auctioneer and, whenever notified of a new bid, decides whether to place a
higher bid of its own.
*/
class Bidder {
    string name;
    double budget;
    double bid_probability;
    double bid_increase_perc;
    double highest_bid;

public:
    Bidder(string name, double budget = 100, double bid_probability = 0.35, double bid_increase_perc = 1.1) :
        name(name), budget(budget), bid_probability(bid_probability), bid_increase_perc(bid_increase_perc), highest_bid(0) {}

    /*
    Called by the auctioneer to notify this bidder that a new bid was
    accepted. The bidder decides whether to retaliate with a new bid of
    its own by calling auctioneer->accept_bid(...).
    :param auctioneer: the Auctioneer that is notifying this bidder.
    */
    void update(Auctioneer *auctioneer);

    // TODO: add any getters you need (e.g. getName(), getHighestBid()) so
    // Auction can print the end-of-auction summary.

    friend ostream& operator<<(ostream &os, const Bidder& bidder) {
        os << bidder.name;
        return os;
    }
};
