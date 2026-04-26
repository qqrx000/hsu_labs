#include "kan.h"
#include "bitMatrix.h"
#include "queue.h"

#define BITS_PER_WORD 64

int topoSort(const int n, const bitMatrix *adj, short *inDegree,
             short *result) {
  if (!adj || !inDegree || !result || n <= 0)
    return 0;

  queue *q = createQueue(n);
  if (!q)
    return 0;

  for (int i = 1; i <= n; i++) {
    if (inDegree[i] == 0) {
      push(q, (short)i);
    }
  }

  int count = 0;
  const int wordsPerRow = getWordsPerRow(adj);
  const unsigned int *data = getData(adj);

  while (!isEmpty(q)) {
    const short u = pop(q);
    result[count++] = u;

    for (int v = 1; v <= n; v++) {
      const int wordIdx = u * wordsPerRow + v / BITS_PER_WORD;
      const int bitIdx = v % BITS_PER_WORD;

      if (data[wordIdx] >> bitIdx & 1) {
        if (--inDegree[v] == 0) {
          push(q, (short)v);
        }
      }
    }
  }

  freeQueue(q);
  return count == n;
}
