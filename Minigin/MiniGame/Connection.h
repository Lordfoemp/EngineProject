#pragma once
namespace Helheim
{
	class Cube;
	class Connection final
	{
		public:
			Connection(Cube* pCube1, Cube* pCube2);
			~Connection() = default;

			Connection(const Connection&) = delete;
			Connection(Connection&&) noexcept = delete;
			Connection& operator=(const Connection&) = delete;
			Connection& operator=(Connection&&) noexcept = delete;

			Cube* GetCube1() const { return m_pCube1; }
			Cube* GetCube2() const { return m_pCube2; }

		protected:

		private:
			Cube* m_pCube1;
			Cube* m_pCube2;
	};
}