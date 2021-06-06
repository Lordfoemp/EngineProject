#pragma once
namespace Helheim
{
	class GameObject;
	//class Disc;
	class Connection final
	{
		public:
			Connection(GameObject* pCube1, GameObject* pCube2, bool connectedToDisc);
			~Connection() = default;

			Connection(const Connection&) = delete;
			Connection(Connection&&) noexcept = delete;
			Connection& operator=(const Connection&) = delete;
			Connection& operator=(Connection&&) noexcept = delete;

			GameObject* GetCube1() const { return m_pCube1; }
			GameObject* GetCube2() const { return m_pCube2; }
			GameObject* GetDisc() const { return m_pDisc; }

		protected:

		private:
			GameObject* m_pCube1;
			GameObject* m_pCube2;
			GameObject* m_pDisc;
	};
}