#pragma once

template <typename T>
class List {
public:
	List<T>* head;
	List() {
		head = nullptr;
		next = nullptr;
	}

	~List() {
		clear();
	}

	void append(T value) {
		List<T>* temp = new List<T>();
		temp->data = value;
		temp->next = nullptr;
		if (!head) {
			head = temp;
		}
		else {
			List<T>* curr = head;
			while (curr->next) {
				curr = curr->next;
			 }
			curr->next = temp;
		}
	}

	void clear() {
		while (head) {
			List<T>* temp = head;
			head = head->next;
			delete temp;
		 }
	}

	T getData() {
		return data;
	}

	List<T>* getNext() {
		return next;
	}
private:
	T data;
	List* next;
};
