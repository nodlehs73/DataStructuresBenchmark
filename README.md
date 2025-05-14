# Benchmarks for Splay Tree, Skip List & Tango Tree  

---

## 1 • Subset Search Benchmark  
_(hot-subset size vs. total search time)_

![Subset Search Benchmark – hot subset sweep](plot9.png)

| Parameter | Value |
|-----------|-------|
| Inserted keys | `N = 10 000 000` |
| Searches      | `N` searches drawn only from a hot subset |
| Subset size   | `p%` of `N`, `p ∈ {0.0001 … 75}` |

---

## 2 • Sequential Insert-Only  

![Sequential inserts](plot1.png)

Insert keys `1…N` in order (no search/delete).  
Shows build-cost on a degenerate increasing sequence.

---

## 3 • Random Insert-Only  

![Random inserts](plot8.png)

Same as (2) but keys arrive in random order.

---

## 4 • Random Deletion  

![Random deletes](plot2.png)

Start with random inserts, then delete `N` random keys.

---

## 5 • Sequential Deletion  

![Sequential deletes](plot3.png)

Insert sequentially, delete sequentially (`1…N`).

---

## 6 • Random Search  

![Random search](plot4.png)

After random build, perform `N` uniform-random searches.

---

## 7 • Sequential Search  

![Sequential search](plot5.png)

After sequential build, search keys in ascending order once.

---

## 8 • Random Search + Delete  

![Random search+delete](plot6.png)

Mixed workload: 50 % random searches, 50 % random deletes.

---

## 9 • Sequential Search + Delete  

![Sequential search+delete](plot7.png)

Search keys `1…N`, then delete the same sequence.

