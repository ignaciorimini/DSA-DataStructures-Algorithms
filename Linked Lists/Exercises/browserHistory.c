#include <stdio.h>
#include <stdlib.h>

// Solution to the following problem: https://leetcode.com/problems/design-browser-history/
// Difficulty: Medium

typedef struct _BrowserHistory{
    char* actualPage;
    struct _BrowserHistory* forward;
    struct _BrowserHistory* back;
} BrowserHistory;

BrowserHistory* browserHistoryCreate(char * homepage) {
    BrowserHistory* browser= malloc(sizeof(BrowserHistory));
    browser->actualPage= homepage;
    browser->forward= NULL;
    browser->back= NULL;
    return browser;
}

void browserHistoryVisit(BrowserHistory* obj, char * url) {
    BrowserHistory* newPage= malloc(sizeof(BrowserHistory));
    newPage->actualPage= obj->actualPage;
    newPage->forward= obj;
    newPage->back= obj->back;
    obj->back= newPage;
    obj->actualPage= url;
}

char * browserHistoryBack(BrowserHistory* obj, int steps) {
    while(obj->back != NULL && steps != 0){
        steps--;
        obj= obj->back;
    }

    return obj->actualPage;
}

char * browserHistoryForward(BrowserHistory* obj, int steps) {
    while(obj->forward != NULL && steps != 0){
        steps--;
        obj= obj->forward;
    }

    return obj->actualPage;
}

void browserHistoryFree(BrowserHistory* obj) {
    
}

/**
 * Your BrowserHistory struct will be instantiated and called as such:
 * BrowserHistory* obj = browserHistoryCreate(homepage);
 * browserHistoryVisit(obj, url);
 
 * char * param_2 = browserHistoryBack(obj, steps);
 
 * char * param_3 = browserHistoryForward(obj, steps);
 
 * browserHistoryFree(obj);
*/

int main(){
    BrowserHistory* browser= browserHistoryCreate("www.google.com");
    browserHistoryVisit(browser, "www.facebook.com");
    browserHistoryVisit(browser, "www.youtube.com");
    printf("Returning back: %s\n", browserHistoryBack(browser, 1));
    printf("Forward page: %s\n", browserHistoryForward(browser, 1));
    return 0;
}