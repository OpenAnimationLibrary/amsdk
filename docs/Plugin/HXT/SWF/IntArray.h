class IntArray
{
public:
	CArray<int, int> arr;
	int size;

	IntArray()
	{
		size = 0;
	}

	~IntArray()
	{
		arr.RemoveAll();
	} 

	int GetAt(int index)
	{
		arr.GetAt(index);
	}

	void Add(int value)
	{
		arr.Add(value);
		size++;
	}
};