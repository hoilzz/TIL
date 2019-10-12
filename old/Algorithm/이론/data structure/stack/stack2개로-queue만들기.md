# stack 2개로 큐 만들기

각각 enqueue, dequeue용으로 스택을 이용한다.


```C
class Queue {
public:
    stack<int> enQBox;
    stack<int> deQBox;
    
    void enqueue(int value) {
        enQBox.push(value);
    }
    
    int dequeue() {
        while(!enQBox.empty()) {
            int value = enQBox.top();
            deQBox.push(value);
            enQBox.pop();
        }
        int valueDequeued = deQBox.top();
        deQBox.pop();
        return valueDequeued;
    }
};


int main(int argc, const char * argv[]) {
    
    Queue* q1 = new Queue();
    q1->enqueue(1);
    q1->enqueue(2);
    q1->enqueue(3);
    
    printf("%d\n", q1->dequeue());
    printf("%d\n", q1->dequeue());
    printf("%d\n", q1->dequeue());
    
    return 0;
}
```