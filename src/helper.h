

bool containsInt(int* hey, int needle ) { 
    int n = *(&hey + 1) - hey;
    for (int i=0; i < n;i++) {
        // Serial.printf("i=%d, hey=%d, needle=%d, n=%d\n %d/%d -- %d", i, hey[i], needle,n, sizeof(hey), sizeof(hey[0]), *(&hey + 1) - hey);
        if (hey[i] == needle) return true;
    }
    return false;
};