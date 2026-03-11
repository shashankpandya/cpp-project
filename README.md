# Cash Flow Minimizer (C++)

A C++ command-line program that **minimizes the number of cash transactions** required to settle debts among multiple banks.

Given a set of banks, their supported payment modes, and a list of directed transactions (debts), the program computes each bank’s net balance and produces a simplified set of payments that settles everyone’s balance. When two banks don’t share any payment mode, the program falls back to an intermediary mode labeled `WorldBank`.

## How it works (high level)

1. Reads banks and their supported payment modes.
2. Reads a list of transactions `(from -> to, amount)` and computes each bank’s **net amount**:
   - payer (`from`) decreases net amount
   - receiver (`to`) increases net amount
3. Repeatedly matches:
   - the bank with the **maximum positive** net amount (creditor)
   - the bank with the **maximum negative** net amount (debtor)
   and transfers the minimum amount needed to reduce one of them toward zero.
4. Prints the minimized settlement transactions.

## Build

Requires a C++ compiler (e.g. `g++`) with C++11 (or newer) support.

```bash
g++ -std=c++11 -O2 -o cash_flow_minimizer "CASH FLOW MINIMIZER.cpp"
```

## Run

```bash
./cash_flow_minimizer
```

The program is interactive and will prompt you for input.

## Input format (interactive prompts)

1. **Number of banks**
2. For each bank:
   - bank name (single word)
   - number of payment modes
   - list of payment modes (each single word)
3. **Number of transactions**
4. For each transaction:
   - `from to amount`

Notes:
- Bank names and payment modes are read using `cin >>`, so they must not contain spaces.
- Amounts are integers.

## Example

Example session (user input shown after prompts):

```text
Enter number of banks: 3

Bank 1 name: A
Enter number of payment modes: 2
Enter payment modes: UPI NEFT

Bank 2 name: B
Enter number of payment modes: 2
Enter payment modes: UPI IMPS

Bank 3 name: C
Enter number of payment modes: 1
Enter payment modes: NEFT

Enter number of transactions: 3
Transaction 1 (from to amount): A B 100
Transaction 2 (from to amount): B C 50
Transaction 3 (from to amount): A C 30

Minimized Transactions:
...
```

## Files

- `CASH FLOW MINIMIZER.cpp` — main program.

## Limitations / assumptions

- Uses a greedy matching between the largest creditor and largest debtor.
- Uses `int` for amounts; very large totals could overflow (consider `long long` if needed).
- If there is no shared payment mode between a debtor/creditor pair, the settlement is labeled `WorldBank` (intermediary fallback).
