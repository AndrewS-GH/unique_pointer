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
		delete m_data;	
	}

	// no copy or assignment
	UniquePointer(const UniquePointer& up) = delete;
	UniquePointer& operator=(const UniquePointer& up) = delete;

	// Move
	UniquePointer(UniquePointer&& up) noexcept
		: m_data{ up.m_data }
	{
		up.m_data = nullptr;
	}

	UniquePointer& operator=(UniquePointer&& up)
	{
		if (&up == this)
			return *this;

		// transfer ownership
		delete m_data;
		m_data = up.m_data;
		up.m_data = nullptr;

		return *this;
	}

	T& operator*() const { return *m_data; }
	T* operator->() const { return m_data; }

	// Modifiers
	T* release()
	{
		T* temp{ m_data };
		m_data = nullptr;
		return temp;
	}
	
	void reset(T* data)
	{
		if (m_data)
			delete m_data;
		m_data = data;
	}

	void swap(UniquePointer& up)
	{
		T* temp{ up.release() };
		
		up = std::move(*this);
		m_data = temp;

	}
	
	T* get() const { return m_data; }
	operator bool() const { return static_cast<bool>(m_data); }

	friend bool operator==(const UniquePointer& up1, const UniquePointer& up2) { return up1.get() == up2.get(); }
	friend bool operator!=(const UniquePointer& up1, const UniquePointer& up2) { return up1.get() != up2.get(); }
	

	template<typename T>
	friend UniquePointer& make_unique(T* data)
	{
		return UniquePointer<T>(data);
	}

	friend std::ostream& operator<<(std::ostream& out, const UniquePointer& up)
	{
		out << up.get();
		return out;
	}

};

