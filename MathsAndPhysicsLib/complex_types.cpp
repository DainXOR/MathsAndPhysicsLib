#include "complex_types.h"

namespace dmt {
	//using dmputils::constrains::MathType;

	//template<MathType ty_>
	//constexpr complex<ty_>::complex() noexcept
	//	: m_Coordinates({ buffer_type(), buffer_type() }), m_Traits(Traits(RECTANGULAR))
	//{
	//}

	//template<MathType ty_>
	//constexpr complex<ty_>::complex(const_reference real_, similar_const_ref imaginary_) noexcept
	//	: m_Coordinates({ imaginary_, real_ }), m_Traits(Traits{ RECTANGULAR | DEGREES })
	//{}

	//template<MathType ty_>
	//constexpr complex<ty_>::complex(const_reference magnitude_, similar_const_ref angle_, const Traits& traits_) noexcept
	//	: m_Coordinates({ magnitude_, angle_ }), m_Traits(Traits(POLAR | traits_))
	//{}

	//template<MathType ty_>
	//constexpr complex<ty_>::complex(const vector<buffer_type, 2>& Coordinates_, const Traits& traits_) noexcept
	//	: m_Coordinates(Coordinates_), m_Traits(traits_)
	//{}

	//template<MathType ty_>
	//constexpr complex<ty_>::complex(const_type first_, const_type second_, const Traits traits_) noexcept
	//	: m_Coordinates({ first_, second_ }), m_Traits(traits_)
	//{
	//	(m_Traits & POLAR) || (m_Traits = RECTANGULAR);
	//	return;
	//}


	//template<MathType ty_>
	//complex<ty_>::operator int() const noexcept { return int(real()); }
	//template<MathType ty_>
	//complex<ty_>::operator long() const noexcept { return long(real()); }
	//template<MathType ty_>
	//complex<ty_>::operator short() const noexcept { return short(real()); }
	//template<MathType ty_>
	//complex<ty_>::operator float() const noexcept { return float(real()); }
	//template<MathType ty_>
	//complex<ty_>::operator double() const noexcept { return real(); }
	//template<MathType ty_>
	//complex<ty_>::operator char() const noexcept { return char(real()); }
	//template<MathType ty_>
	//complex<ty_>::operator bool() const noexcept { return bool(magnitude()); }
	//template<MathType ty_>
	//complex<ty_>::operator std::string() const noexcept
	//{ 
	//	if ((getCoordType() & POLAR)) {
	//		std::string formatStr = "(" +	std::to_string(magnitude()) + ", " +
	//										std::to_string(angle()) + ")";
	//		return formatStr;
	//	}
	//
	//	std::string formatStr = std::to_string(real()) + " + " +
	//							std::to_string(imaginary()) + "i";
	//	return formatStr;
	//}
	//template<MathType ty_>
	//complex<ty_>::operator _complex() const noexcept{return _complex({ real(), imaginary() });}

	
	/// 

	//template<MathType ty_>
	//constexpr static complex<ty_> complex<ty_>::rectangularCoords(const_reference magnitude_, similar_const_ref angle_, const Traits& traits_) noexcept
	//{
	//	buffer_type x = magnitude_ * cos(angle_);
	//	buffer_type y = magnitude_ * sin(angle_);
	//
	//	return complex<buffer_type>(x, y);
	//}
	//
	//template<MathType ty_>
	//bool complex<ty_>::rectangularCoords()
	//{
	//	if (!getCoordType()) // Returns non cero if polar coords
	//		return false;
	//
	//	buffer_type x = m_Coordinates.value(0) * cos(m_Coordinates.value(1));
	//	buffer_type y = m_Coordinates.value(0) * sin(m_Coordinates.value(1));
	//	m_Coordinates = { x, y };
	//	return true;
	//}

	//template<MathType ty_>
	//constexpr static complex<ty_> complex<ty_>::polarCoords(const_reference real_, similar_const_ref imaginary_, const Traits& traits_) noexcept
	//{
	//	buffer_type m = sqrt(pow(real_, 2) + pow(imaginary_, 2));
	//	buffer_type a = atan(real_ / imaginary_);
	//
	//	return complex(m, a, traits_);
	//}
	//
	//template<MathType ty_>
	//bool complex<ty_>::polarCoords()
	//{
	//	if (getCoordType()) // Returns non cero if polar coords
	//		return false;
	//
	//	buffer_type r = sqrt(pow(m_Coordinates.value(0), 2) + pow(m_Coordinates.value(1), 2));
	//	float a = atan(m_Coordinates.value(0) / m_Coordinates.value(1));
	//	m_Coordinates = { r, a };
	//	return true;
	//}

	//template<MathType ty_>
	//ty_ complex<ty_>::real() {
	//	buffer_type val = 0;
	//	(!getCoordType()) && (val = m_Coordinates);
	//
	//	return val;
	//}
	//template<MathType ty_>
	//ty_ complex<ty_>::imaginary() {
	//	return dgt::real();
	//}
	//template<MathType ty_>
	//ty_ complex<ty_>::magnitude() {
	//	return dgt::real();
	//}
	//template<MathType ty_>
	//ty_ complex<ty_>::angle() {
	//	return dgt::real();
	//}
	//template<MathType ty_>
	//bool complex<ty_>::radians() const{
	//	return bool(m_Traits & RADIANS);
	//}

	//template<MathType ty_>
	//complex<ty_> complex<ty_>::operator=(complex<similar> other_) { return other_; }
	//template<MathType ty_>
	//complex<ty_> complex<ty_>::operator=(similar real_) { return complex(real_, 0); }
	//
	//template<MathType ty_>
	//complex<ty_> complex<ty_>::operator+(complex<similar> other_)
	//{
	//	return { this->real()		+ other_.real(), 
	//			 this->imaginary()	+ other_.imaginary() };
	//}
	//template<MathType ty_>
	//complex<ty_> complex<ty_>::operator+(similar real_) { return { this->real() + real_, this->imaginary() }; }
	//
	//template<MathType ty_>
	//complex<ty_> complex<ty_>::operator-(complex<similar> other_)
	//{
	//	return { this->real() - other_.real(),
	//			 this->imaginary() - other_.imaginary() };
	//}
	//template<MathType ty_>
	//complex<ty_> complex<ty_>::operator-(similar real_) { return { this->real() - real_, this->imaginary() }; }
	//
	//template<MathType ty_>
	//complex<ty_> complex<ty_>::operator*(complex<similar> other_)
	//{
	//	return { this->real() * other_.real(),
	//			 this->imaginary() * other_.imaginary() };
	//}
	//template<MathType ty_>
	//complex<ty_> complex<ty_>::operator*(similar real_) { return { this->real() * real_, this->imaginary() }; }
	//
	//template<MathType ty_> 
	//complex<ty_> complex<ty_>::operator/(complex<similar> other_)
	//{
	//	return { this->real() / other_.real(),
	//			 this->imaginary() / other_.imaginary() };
	//}
	//template<MathType ty_>
	//complex<ty_> complex<ty_>::operator/(similar real_) { return { this->real() / real_, this->imaginary() }; }

	//template<MathType ty_>
	//complexTraits complex<ty_>::getCoordType() { return complexTraits( m_Traits & POLAR ); }

	


	//namespace {
	//	void _() {
	//		complex _;
	//	}
	//}
}

