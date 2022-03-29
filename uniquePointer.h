// a rough unique pointer implementation
// templated class to manage memory of dynamically created objects
// no two unique pointers can point to the same object

#pragma once

template<class T>
class UniquePointer
{
private:
	T* m_data{};

public:
	UniquePointer(T* data = nullptr)
		: m_data{ data }
	{
	}

	~UniquePointer()
	{
		if (m_data) // delete if not nullptr
			delete m_data;
	}

	// no copy or assignment
	UniquePointer(const UniquePointer& up) = delete;
	UniquePointer& operator=(const UniquePointer& up) = delete;

	// Move Constructor
	UniquePointer(UniquePointer&& up) noexcept
		: m_data{ up.m_data }
	{
		up.m_data = nullptr; // ownership transfer, set original to nullptr
	}

	// R-Value Ref assignment
	UniquePointer& operator=(UniquePointer&& up)
	{
		if (&up == this)
			return *this;

		// transfer ownership
		if (m_data)
			delete m_data;
		m_data = up.m_data;
		up.m_data = nullptr;

		return *this;
	}

	T& operator*() const { return *m_data; }
	T* operator->() const { return m_data; }

	// returns a pointer to managed object, releases ownership
	T* release()
	{
		T* temp{ m_data };
		m_data = nullptr;
		return temp;
	}

	// replaces the managed object
	void reset(T* data)
	{
		if (m_data) // delete if not nullptr
			delete m_data;
		m_data = data;
	}

	// swaps the managed objects
	void swap(UniquePointer& up)
	{
		T* temp{ up.release() };

		up = std::move(*this); // calls R-Value Reference assignment
		m_data = temp;

	}

	T* get() const { return m_data; }
	operator bool() const { return static_cast<bool>(m_data); }

	friend bool operator==(const UniquePointer& up1, const UniquePointer& up2) { return up1.get() == up2.get(); }
	friend bool operator!=(const UniquePointer& up1, const UniquePointer& up2) { return up1.get() != up2.get(); }


};

template<typename T>
std::ostream& operator<<(std::ostream& out, const UniquePointer<T>& up)
{
	out << up.get();
	return out;
}


template<typename T>
UniquePointer<T> make_unique(T&& data)
{
	return UniquePointer<T>(new T(data));
}
