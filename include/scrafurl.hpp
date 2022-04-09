/*
 * SPDX-FileCopyrightText: 2022 Andrea Pappacoda
 *
 * SPDX-License-Identifier: LGPL-3.0-or-later
 */

#pragma once

#include <curl/curl.h>
#include <mutex>
#include <string>
#include <array>
#include <concepts>

// NULL-terminated std::string_view
template<typename type>
concept Text = std::convertible_to<type, std::string_view> && (std::convertible_to<type, std::string> || std::convertible_to<type, const char*>);

class Scrafurl {
public:
	Scrafurl();
	~Scrafurl();

	void get(const std::string_view url, const Text auto... headers) noexcept {
		_response_body.clear();
		curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
		curl_easy_setopt(curl, CURLOPT_URL, url.data());
		struct curl_slist* curl_headers {nullptr};
		if constexpr (sizeof...(headers) != 0) {
			const std::array header_array {static_cast<std::string_view>(headers)...};
			for (const std::string_view header : header_array) {
				curl_headers = curl_slist_append(curl_headers, header.data());
			}
		}
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, curl_headers);
		curl_easy_perform(curl);
		curl_slist_free_all(curl_headers);
	}

	void post(const std::string_view url, const std::string_view request, const Text auto... headers) noexcept {
		_response_body.clear();
		curl_easy_setopt(curl, CURLOPT_POST, 1L);
		curl_easy_setopt(curl, CURLOPT_URL, url.data());
		struct curl_slist* curl_headers {nullptr};
		if constexpr (sizeof...(headers) != 0) {
			const std::array header_array {static_cast<std::string_view>(headers)...};
			for (const std::string_view header : header_array) {
				curl_headers = curl_slist_append(curl_headers, header.data());
			}
		}
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, curl_headers);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, request.data());
		curl_easy_perform(curl);
		curl_slist_free_all(curl_headers);
	}

	void put(const std::string_view url, const std::string_view request, const Text auto... headers) noexcept {
		_response_body.clear();
		curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");
		curl_easy_setopt(curl, CURLOPT_URL, url.data());
		struct curl_slist* curl_headers {nullptr};
		if constexpr (sizeof...(headers) != 0) {
			const std::array header_array {static_cast<std::string_view>(headers)...};
			for (const std::string_view header : header_array) {
				curl_headers = curl_slist_append(curl_headers, header.data());
			}
		}
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, curl_headers);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, request.data());
		curl_easy_perform(curl);
		curl_slist_free_all(curl_headers);
	}

	void patch(const std::string_view url, const std::string_view request, const Text auto... headers) noexcept {
		_response_body.clear();
		curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PATCH");
		curl_easy_setopt(curl, CURLOPT_URL, url.data());
		struct curl_slist* curl_headers {nullptr};
		if constexpr (sizeof...(headers) != 0) {
			const std::array header_array {static_cast<std::string_view>(headers)...};
			for (const std::string_view header : header_array) {
				curl_headers = curl_slist_append(curl_headers, header.data());
			}
		}
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, curl_headers);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, request.data());
		curl_easy_perform(curl);
		curl_slist_free_all(curl_headers);
	}

	void deletee(const std::string_view url, const Text auto... headers) noexcept {
		_response_body.clear();
		curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");
		curl_easy_setopt(curl, CURLOPT_URL, url.data());
		struct curl_slist* curl_headers {nullptr};
		if constexpr (sizeof...(headers) != 0) {
			const std::array header_array {static_cast<std::string_view>(headers)...};
			for (const std::string_view header : header_array) {
				curl_headers = curl_slist_append(curl_headers, header.data());
			}
		}
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, curl_headers);
		curl_easy_perform(curl);
		curl_slist_free_all(curl_headers);
	}

	[[nodiscard]] long get_response_code() const noexcept;

	[[nodiscard]] const std::string& get_response_body() const noexcept;

	enum class HttpVersion : long {
		v1_1 = CURL_HTTP_VERSION_1_1,
		v2 = CURL_HTTP_VERSION_2,
		v2_tls = CURL_HTTP_VERSION_2TLS,
		// v3 = CURL_HTTP_VERSION_3 requires libcurl 7.66.0
	};

private:
	CURL* curl;
	std::string _response_body;
	long _response_code;
	static std::once_flag _is_curl_initialised;

private:
	static std::size_t write_data(char* incomingBuffer, std::size_t size, std::size_t count, std::string* data);
};
