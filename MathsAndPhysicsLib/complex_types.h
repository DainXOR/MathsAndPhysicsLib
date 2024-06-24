#pragma once
#include <string>
#include <cmath>
#include <ostream>

#include "dmtdeclarations.h"
#include "general_utilities.h"

_DMP_BEGIN

namespace imaginary_ns {
	namespace tests {
		using dmutils::constrains::MathType;

		template <MathType value_type>
		class imaginary {
		public:
			using type = value_type;
			using const_type = const type;
			using pointer = type*;
			using const_pointer = const type*;
			using reference = type&;
			using const_reference = const type&;

			

		public:
			type value;

		};

		template <MathType value_type>
		class real {
		public:
			using type = value_type;
			using const_type = const type;
			using pointer = type*;
			using const_pointer = const type*;
			using reference = type&;
			using const_reference = const type&;

		public:
			type value;

		};
	}
	namespace works {
	}
}

namespace dmt {
	using dmutils::constrains::MathType;
	using namespace dmutils::structs;

	enum complexTraits : unsigned char {
		RECTANGULAR		= 0b0000,
		POLAR			= 0b0001,

		DEGREES			= 0b0000,
		RADIANS			= 0b0010

	};



	template<MathType value_type = dgt::real>
	class complex
	{
		using buffer_type = value_type;
		using const_type = const value_type;
		using pointer = value_type*;
		using const_pointer = const value_type*;
		using reference = value_type&;
		using const_reference = const value_type&;

		using similar = std::type_identity_t<value_type>;
		using similar_const = const std::type_identity_t<value_type>;
		using similar_ptr = std::type_identity_t<value_type>*;
		using similar_const_ptr = const std::type_identity_t<value_type>*;
		using similar_ref = std::type_identity_t<value_type>&;
		using similar_const_ref = const std::type_identity_t<value_type>&;

		using Traits = complexTraits;

	private:
		std::array<buffer_type, 2> m_Coordinates;
		Traits m_Traits = RECTANGULAR;

	public:
		/// > Constructors

		/// \param real_		Real part of the complex number.
		/// \param imaginary_	Imaginary part of the complex number.
		/// 
		constexpr complex(buffer_type real_, auto imaginary_) noexcept
			: m_Coordinates({ buffer_type(real_), buffer_type(imaginary_) }), m_Traits(RECTANGULAR)
		{}

		/// \param magnitude_	Magnitude of the complex in polar form.
		/// \param angle_		Angle of the complex in polar form.
		/// \note				.angle_ must be in radians.
		/// \param traits_		Defines the desired angle type.
		///	\note				`RADIANS` if is measured in radians.
		///	\note				`DEGREES` if is measured in degrees.
		/// 
		constexpr complex(auto magnitude_, auto angle_, const Traits& traits_) noexcept
			: m_Coordinates({ buffer_type(magnitude_), buffer_type(angle_) }), m_Traits(Traits(POLAR | traits_))
		{}

		/// \param	Coordinates_		Vector of two ^real numbers in the complex.
		/// \tparam vector				Mathematical vector, containing the parameters of the complex.
		/// \note						Second value of the $vector is the .imaginary_ part.
		/// 
		template<MathType other_type>
		constexpr complex(const std::array<other_type, 2>& Coordinates_, const Traits& traits_) noexcept
			: m_Coordinates({ buffer_type(Coordinates_[0]), buffer_type(Coordinates_[1])}), m_Traits(traits_)
		{}

		template<MathType other_type>
		constexpr complex(const complex<other_type>& other_) noexcept
			: m_Coordinates({ buffer_type(other_.values()[0]), buffer_type(other_.values()[1]) }), m_Traits(other_.traits())
		{}


		/// \param first_		First part of the complex number.
		/// \param second_		Second part of the complex number.
		/// \param traits_		Defines the desired angle type.
		///	\note				`RECTANGULAR` if are cartesian coordinates.
		///	\note				`POLAR` if are polar coordinates.
		/// \note				`RADIANS` if is measured in radians.
		/// \note				`DEGREES` if is measured in degrees.
		/// 
		//constexpr complex(const_type first_, const_type second_, const Traits traits_) noexcept;



		/// > Casts

		explicit operator int()				const noexcept { return int(real()); }
		explicit operator long()			const noexcept { return long(real()); }
		explicit operator short()			const noexcept { return short(real()); }
		explicit operator float()			const noexcept { return float(real()); }
		explicit operator double()			const noexcept { return real(); }
		explicit operator char()			const noexcept { return char(real()); }
		explicit operator bool()			const noexcept { return bool(magnitude()); }
		explicit operator std::string()		const noexcept {

			if (getCoordType()) /* True: Polar*/ {
				std::string formatStr = "(" + std::to_string(magnitude()) + ", " +
					std::to_string(angle()) + ")";
				return formatStr;
			}

			std::string formatStr = std::to_string(real()) + " + " +
				std::to_string(imaginary()) + "i";
			return formatStr;
		}
		explicit operator _complex()		const noexcept { return _complex({ real(), imaginary() }); }


		/// > Coordinates Convertions

		// Turns the number into rectangular coordinates
		[[nodiscard("Use the non-static method instead (no input parameters).")]]
		constexpr static complex rectangularCoords(const_reference magnitude_, similar_const_ref angle_, const Traits& traits_) noexcept {
			buffer_type x = magnitude_ * cos(angle_);
			buffer_type y = magnitude_ * sin(angle_);

			return complex<buffer_type>(x, y);
		}
		bool rectangularCoords() noexcept {
			if (!getCoordType()) // Returns non cero if polar coords
				return false;

			buffer_type x = m_Coordinates[0] * cos(m_Coordinates[1]);
			buffer_type y = m_Coordinates[0] * sin(m_Coordinates[1]);
			m_Coordinates = { x, y };
			return true;
		}

		// Turns the number into polar coordinates
		[[nodiscard("Use the non-static method instead (no input parameters).")]]
		constexpr static complex polarCoords(const_reference real_, similar_const_ref imaginary_, const Traits& traits_) noexcept {
			buffer_type m = sqrt(pow(real_, 2) + pow(imaginary_, 2));
			buffer_type a = atan(real_ / imaginary_);

			return complex(m, a, traits_);
		}
		bool polarCoords() noexcept {
			if (getCoordType()) // Returns non cero if polar coords
				return false;

			buffer_type r = sqrt(pow(m_Coordinates[0], 2) + pow(m_Coordinates[1], 2));
			buffer_type a = atan(m_Coordinates[0] / m_Coordinates[1]);
			m_Coordinates = { r, a };
			return true;
		}

		//dgs::pair<>
		std::array<buffer_type, 2>	values()		const noexcept { return this->m_Coordinates; }
		Traits						traits()		const noexcept { return this->m_Traits; }
		buffer_type					real()			const noexcept {
			buffer_type val = 0;
			(!getCoordType()) && (val = m_Coordinates[0]);

			return val;
		}
		buffer_type					imaginary()		const noexcept {
			buffer_type val = 0;
			(!getCoordType()) && (val = m_Coordinates[1]);

			return val;
		}
		buffer_type					magnitude()		const noexcept {
			buffer_type val = 0;
			(getCoordType()) && (val = m_Coordinates[0]);

			return val;
		}
		buffer_type					angle()			const noexcept {
			buffer_type val = 0;
			(getCoordType()) && (val = m_Coordinates[1]);

			return val;
		}
		bool						radians()		const noexcept { return bool(m_Traits & RADIANS); }
		bool						isPolar()		const noexcept { return bool(getCoordType() & POLAR); }
		bool						isRecatngular()	const noexcept { return !bool(getCoordType() & POLAR); }

		/// > Operators

		//template<typename other_type>
		//complex<buffer_type> operator =(const complex<other_type>& other_) const noexcept {
		//	this->m_Coordinates = { other_.m_Coordinates };
		//	this->m_Traits = other_.m_Traits;
		//	return *this;
		//}
		//template<typename other_type>
		//complex<buffer_type> operator =(other_type real_) const noexcept { this->m_Coordinates = { real_, 0 }; }


		template<typename other_type>
		complex<buffer_type> operator +(complex<other_type> other_) const noexcept {
			return { this->real() + buffer_type(other_.real()),
						this->imaginary() + buffer_type(other_.imaginary()) };
		}
		template<typename other_type>
		complex<buffer_type> operator +(other_type real_) const noexcept { return { this->real() + real_, this->imaginary() }; }

		template<typename other_type>
		complex<buffer_type> operator +=(const complex<other_type> &other_) noexcept {
				
			this->m_Coordinates = {	this->real() + buffer_type(other_.real()),
									this->imaginary()	+ buffer_type(other_.imaginary()) };

			return   {	this->real() + buffer_type(other_.real()),
						this->imaginary()	+ buffer_type(other_.imaginary()) };
		}
		template<typename other_type>
		complex<buffer_type> operator +=(other_type real_) const noexcept { 
			this->m_Coordinates = { this->real() + real_, this->imaginary() };
			return { this->real() + real_, this->imaginary() }; 
		}

		template<typename other_type>
		complex<buffer_type> operator -(complex<other_type> other_) const noexcept {
			return { this->real() + other_.real(),
						this->imaginary() + other_.imaginary() };
		}
		template<typename other_type>
		complex<buffer_type> operator -(other_type real_) const noexcept { return { this->real() - real_, this->imaginary() }; }

		template<typename other_type>
		complex<buffer_type> operator -=(complex<other_type> other_) const noexcept {
			this->m_Coordinates = { this->real() - other_.real(),
						this->imaginary() - other_.imaginary() };

			return { this->real() - other_.real(),
						this->imaginary() - other_.imaginary() };
		}
		template<typename other_type>
		complex<buffer_type> operator -=(other_type real_) const noexcept {
			this->m_Coordinates = { this->real() - real_, this->imaginary() };
			return { this->real() - real_, this->imaginary() };
		}


		template<typename other_type>
		complex<buffer_type> operator*(complex<other_type> other_) const noexcept {
			return { this->real() + other_.real(),
						this->imaginary() + other_.imaginary() };
		}
		template<typename other_type>
		complex<buffer_type> operator*(other_type real_) const noexcept { return { this->real() * real_, this->imaginary() }; }

		template<typename other_type>
		complex<buffer_type> operator/(complex<other_type> other_) const noexcept {
			return { this->real() + other_.real(),
						this->imaginary() + other_.imaginary() };
		}
		template<typename other_type>
		complex<buffer_type> operator/(other_type real_) const noexcept { return { this->real() / real_, this->imaginary() }; }


	private:
		Traits getCoordType() const noexcept { return Traits(m_Traits & POLAR); }


	};

	template<typename buffer_type>
	std::ostream& operator<<(std::ostream& out, const complex<buffer_type>& rhs)
	{
		if (rhs.isPolar()) {
			out << "(" << rhs.magnitude() << ", " << rhs.angle() << ")";
			return out;
		}

		std::string op = rhs.imaginary() < 0 ? " - " : " + ";


		out << rhs.real() << op << dmbasic_functions::abs(rhs.imaginary()) << "i";
		return out;
	}
}
_DMP_END