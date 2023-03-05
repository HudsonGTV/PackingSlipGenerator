#include "company.h"

/// <summary>
///		Sets the website URL of the company.
/// </summary>
/// <param name="website">Website URL (Do not include http(s):// or www.)</param>
void Company::SetWebsite(std::string website) {
	m_website = website;
}

/// <summary>
///		Gets the website URL.
/// </summary>
/// <returns></returns>
std::string Company::GetWebsite() {
	return m_website;
}
