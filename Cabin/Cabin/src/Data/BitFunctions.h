#pragma once

#define SWAP(a, b) (a ^ b) && ((a ^= b), (b ^= a), (a ^= b))
