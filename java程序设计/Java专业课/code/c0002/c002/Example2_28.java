public classExample2_28
{
	public static void main(String args[])
	{
		int i;
		int a[]={10,20,30,40,50};
		int b[]={-15,-25,-35,-45,-55,-65,-75};
		
		System.out.println("����a������b��Ԫ�أ�");
		
		for(i=0;i<a.length;i++)
			System.out.printf("%4d", a[i]);
		System.out.println();
		
		for(i=0;i<b.length;i++)
			System.out.printf("%4d", b[i]);
		System.out.println();
		
		a=b;//��ֵ��a��ֵ��b��ֵ��ͬ������ʾ��2������
		
		System.out.println("ִ��\"a=b;\"��,����a������b��Ԫ�أ�");
		
		for(int x:a)//��ǿ��ѭ��
			System.out.printf("%4d", x);
		System.out.println();
		
		for(int x:b)//��ǿ��ѭ��
			System.out.printf("%4d", x);
		System.out.println();		
	}
}
