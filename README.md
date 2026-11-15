# luhn-algorithm-checker

[![CI](https://github.com/m-fin/luhn-algorithm-checker/actions/workflows/ci.yml/badge.svg)](https://github.com/m-fin/luhn-algorithm-checker/actions/workflows/ci.yml)

Reads a card number, checks it with the Luhn algorithm, and prints one line:

`AMEX`, `MASTERCARD`, `VISA`, or `INVALID`.

## Which numbers match

| Result       | Digits   | Prefix                          |
|--------------|----------|---------------------------------|
| `AMEX`       | 15       | 34 or 37                        |
| `MASTERCARD` | 16       | 51, 52, 53, 54, or 55           |
| `VISA`       | 13 or 16 | 4                               |
| `INVALID`    | anything else, a failed checksum, or input that is not a non-negative integer | |

Mastercard's later 2-series range (2221–2720) is not recognized. A published 2-series test number such as `2223003122003222` is `INVALID` here.

## Luhn checksum

Take the digits from the right. The last digit (the check digit) stays as it is. Double every second digit moving left. If doubling produces two digits, add those digits together (16 becomes 1 + 6). Add the results to the digits that were not doubled. The number passes when that total is divisible by 10.

`4111111111111111` passes. Changing the last digit to `4111111111111112` does not.

## Build, run, test

Requirements: `gcc` and `make`.

```bash
make
./luhn
```

```text
Number: 4111111111111111
VISA
```

```bash
make test
make clean
```

`make` compiles `luhn.c` with `-Wall -Wextra -Werror -std=c11`. The `luhn` binary is a build product and is not committed.

`make test` runs `test.sh`. Every passing number in that script is a widely published test number (Stripe's test cards, and the usual textbook samples such as `4012888888881881` and `4222222222222`). They are not real accounts. Failing cases are those numbers with a changed check digit, the wrong length, another brand's published test number, or non-numeric input.

## Continuous integration

GitHub Actions runs `make` and `make test` on `ubuntu-latest` for pushes and pull requests. See [`.github/workflows/ci.yml`](.github/workflows/ci.yml).
