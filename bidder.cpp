#include "bidder.hpp"
#include "auctioneer.hpp"

void Bidder::update(Auctioneer *auctioneer) {
    // TODO: decide whether to retaliate with a new bid. Only bid if:
    //   - the new highest bid wasn't placed by this same bidder
    //   - this bidder's next bid (highest bid * bid_increase_perc) would not
    //     exceed its budget
    //   - a randomly generated probability roll succeeds, per bid_probability
    //     (see Lab-08.pptx on <random> / rand())
    // If all three hold, compute the new bid and call
    // auctioneer->accept_bid(new_bid, this).
}
