#pragma once

template<class T>
class SmartPointer
{
private:
	T* m_data{};

public:
	SmartPointer(T* data = nullptr)
		: m_data{ data }
	{
		
	}

	~SmartPointer()
	{
		delete m_data;	
	}

	// no copy or assignment
	SmartPointer(const SmartPointer& sp) = delete;
	SmartPointer& operator=(const SmartPointer& sp) = delete;

	// Move
	SmartPointer(SmartPointer&& sp) noexcept
		: m_data{ sp.m_data }
	{
		sp.m_data = nullptr;
	}

	SmartPointer& operator=(const SmartPointer&& sp)
	{
		if (&sp == this)
			return *this;

		// transfer ownership
		delete m_data;
		m_data = *sp.m_data;
		*sp.m_data = nullptr;

		return *this;
	}

	T& operator*() const { return *m_data; }
	T* operator->() const { return m_data; }

	// Modifiers
	T* release() { return std::move(m_data); }
	
	void reset(T* data)
	{
		if (m_data)
			delete m_data;
		*m_data = data;
	}

	void swap(SmartPointer& sp)
	{
		T* temp{ sp.release() };
		
		sp = std::move(this);
		m_data = temp;

	}
	
	// Getters
	T* get() const { return m_data; }
	operator bool() const { return static_cast<bool>(m_data); }

	friend bool operator==(const SmartPointer& sp1, const SmartPointer& sp2) { return sp1.get() == sp2.get(); }
	friend bool operator!=(const SmartPointer& sp1, const SmartPointer& sp2) { return sp1.get() != sp2.get(); }
	friend bool operator<(const SmartPointer& sp1, const SmartPointer& sp2) { return sp1.get() < sp2.get(); }
	friend bool operator<=(const SmartPointer& sp1, const SmartPointer& sp2) { return sp1.get() <= sp2.get(); }
	friend bool operator>(const SmartPointer& sp1, const SmartPointer& sp2) { return sp1.get() > sp2.get(); }
	friend bool operator>=(const SmartPointer& sp1, const SmartPointer& sp2) { return sp1.get() >= sp2.get(); }

	template<typename T>
	friend SmartPointer& make_unique(T* data)
	{
		return SmartPointer<T>(data);
	}

	friend std::ostream& operator<<(std::ostream& out, const SmartPointer& sp)
	{
		out << *sp.m_data;
		return out;
	}

};

