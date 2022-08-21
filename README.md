# PRIME BLOCKS AND CONNECTORS

The purpose of this repository is to programmatically generate prime `blocks`
and `connectors`, which are defined by the equation
t(n+1) - t(n) = &plusmn;p, p &isin; &#x2119; and t(n+k) - t(n) = &plusmn; p, p &isin; &#x2119;

## Find Blocks: `stack`

The main program asks for the value of k, size 1.
and stores it in a void pointer.
The sum of all integers in the block is stored in the following byte of memory.
The space allocated for this void pointer is 10;
the remaining space being allocated to the address of the output space.
`stack` itself repeatedly creates random sets of primes and
checks if they are valid with `c_bk`.
If so: `stack` records to aforementioned output space with `wr`
and proceeds to check if more `block`s are requested.
The ultimate `block` produced is then `pack`ed into a new ticket (`tckt_`).

##  Find Connectors: `search`

`search` is similar to `stack` in that both repeatedly check random numbers.
`search` uses `c_ct` instead of `c_bk`; the conditions for a `connector`
are different&mdash;more stringent&mdash;than those for a `block`.
The `connector` structure has internal metadata, unlike a `block`.
Metadata is created within the `search` function, if the `connector` passes the check.

## Usage of `blocks` and `connectors`

Whereas a `block` or `connector` is based on a sequence of integers,
thus the `block` or `connector` can be replaced by them in a sequence.
Therefore, with a `block b` and a `connector c`,
one can create a prime distance graph of the following format.

`b, b, ..., b, c, -b, -b, ..., -b, -c`

The restrictions placed upon `block`s and `connector`s
are such that if they are met,
this sequence will meet the requirements for a prime distance graph. 
