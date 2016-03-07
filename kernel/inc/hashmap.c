#include "hashmap.h"

static const uint32 __shrinkTrigger = GROWTH_FACTOR * 4;

hashmap_t hashmap_init() {
    hashmap_t rl;
    rl.capt = GROWTH_FACTOR;
    rl.size = 0;
    rl.data = (tuple_t*) kmalloc(rl.capt * sizeof(tuple_t));
    return rl;
}

static void __set_resize(hashmap_t* set, uint32 amount) {
    uint32 tempCapt;
    if(amount < set->size) { //Don't let it resize to less than lst->size
        tempCapt = set->size;
    } else {
        tempCapt = amount;
    }
    if(tempCapt == set->capt) {
        return; //There is no need to resize
    }
    set->capt = tempCapt;
    tuple_t* oldData = set->data;
    set->data = (tuple_t*) kmalloc(set->capt * sizeof(tuple_t));
    memcpy(set->data, oldData, set->size * sizeof(tuple_t));
    kfree(oldData);
}

static uint32 __vhashmap_indexOf(hashmap_t rl, string k) {
    int cmpHash = strHash(k);
    tuple_t tmp;
    for(uint32 i = 0; i < rl.size; i++) {
        tmp = rl.data[i];
        if((cmpHash == tmp.hash) && streql(k, tmp.key)) {
            return i;
        }
    }
    return rl.size;
}

tuple_t tuple_initNull() {
    tuple_t tp;
    tp.hash = 0;
    tp.key = NULL;
    tp.val = makeNullElement();
    return tp;
}

element_t hashmap_rmFirst(hashmap_t* map, string key) {
    uint32 pos = __vhashmap_indexOf(*map, key);
    if(pos < map->size) {
        element_t tp = map->data[pos].val;
        map->data[pos] = tuple_initNull();
        return tp;
    }
    return makeNullElement();
}

element_t* hashmap_rmAll(hashmap_t* map, string key) {
    element_t* msg = (element_t*) kmalloc(map->size * sizeof(element_t));
    element_t test = makeNullElement();
    element_t tmp;
    do {
        tmp = hashmap_rmFirst(map, key);
        *msg++ = tmp;
    } while(!eqlElement_t(tmp, test));
    return msg;
}

void hashmap_merge(hashmap_t* dest, hashmap_t src) {
    tuple_t t;
    for(uint32 i = 0; i < src.size; i++) {
        t = src.data[i];
        hashmap_add(dest, t.key, t.val);
    }
}

void hashmap_add(hashmap_t* rl, string s, element_t e) {
    uint32 pos = __vhashmap_indexOf(*rl, s);
    if(pos < rl->size) {
        rl->data[pos].val = e;
    } else {
        if (rl->size == rl->capt) {
            __set_resize(rl, rl->size + GROWTH_FACTOR);
        }
        rl->data[rl->size] = tuple_init(s, e);
        rl->size++;
    }
}

inline bool hashmap_hasKey(hashmap_t rl, string k) {
    return __vhashmap_indexOf(rl, k) < rl.size;
}

element_t hashmap_getVal(hashmap_t rl, string k) {
    uint32 pos = __vhashmap_indexOf(rl, k);
    if(pos < rl.size) {
        return rl.data[pos].val;
    }
    return makeNullElement();
}

void hashmap_destroy(hashmap_t* map) {
    kfree(map->data);
    map->size = map->capt = 0;
}

tuple_t tuple_init(string k, element_t v) {
    tuple_t msg;
    msg.key = k;
    msg.val = v;
    msg.hash = strHash(k);
    return msg;
}
