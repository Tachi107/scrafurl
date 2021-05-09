#pragma once

#include <curl/curl.h>
#include <mutex>
#include <string>
#include <array>
#include <concepts>

class Scrafurl {
public:
	Scrafurl();
	~Scrafurl();

	void get(const std::string_view url, const std::convertible_to<std::string_view> auto... headers) noexcept {
		_responseBody.clear();
		curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
		curl_easy_setopt(curl, CURLOPT_URL, url.data());
		struct curl_slist* curlHeaders {nullptr};
		const std::array headerArray {headers...};
		for (const std::string_view header : headerArray) {
			curlHeaders = curl_slist_append(curlHeaders, header.data());
		}
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, curlHeaders);
		curl_easy_perform(curl);
	}

	void post(const std::string_view url, const std::string_view request, const std::convertible_to<std::string_view> auto... headers) noexcept {
		_responseBody.clear();
		curl_easy_setopt(curl, CURLOPT_POST, 1L);
		curl_easy_setopt(curl, CURLOPT_URL, url.data());
		struct curl_slist* curlHeaders {nullptr};
		const std::array headerArray {headers...};
		for (const std::string_view header : headerArray) {
			curlHeaders = curl_slist_append(curlHeaders, header.data());
		}
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, curlHeaders);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, request.data());
		curl_easy_perform(curl);
	}

	void put(const std::string_view url, const std::string_view request, const std::convertible_to<std::string_view> auto... headers) noexcept {
		_responseBody.clear();
		curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");
		curl_easy_setopt(curl, CURLOPT_URL, url.data());
		struct curl_slist* curlHeaders {nullptr};
		const std::array headerArray {headers...};
		for (const std::string_view header : headerArray) {
			curlHeaders = curl_slist_append(curlHeaders, header.data());
		}
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, curlHeaders);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, request.data());
		curl_easy_perform(curl);
	}

	void patch(const std::string_view url, const std::string_view request, const std::convertible_to<std::string_view> auto... headers) noexcept {
		_responseBody.clear();
		curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PATCH");
		curl_easy_setopt(curl, CURLOPT_URL, url.data());
		struct curl_slist* curlHeaders {nullptr};
		const std::array headerArray {headers...};
		for (const std::string_view header : headerArray) {
			curlHeaders = curl_slist_append(curlHeaders, header.data());
		}
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, curlHeaders);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, request.data());
		curl_easy_perform(curl);
	}

	void deletee(const std::string_view url, const std::convertible_to<std::string_view> auto... headers) noexcept {
		_responseBody.clear();
		curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");
		curl_easy_setopt(curl, CURLOPT_URL, url.data());
		struct curl_slist* curlHeaders {nullptr};
		const std::array headerArray {headers...};
		for (const std::string_view header : headerArray) {
			curlHeaders = curl_slist_append(curlHeaders, header.data());
		}
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, curlHeaders);
		curl_easy_perform(curl);
	}

	[[nodiscard]] long getResponseCode() const noexcept;

	[[nodiscard]] const std::string& getResponseBody() const noexcept;

	enum class HttpVersion : long {
		v1_1 = CURL_HTTP_VERSION_1_1,
		v2 = CURL_HTTP_VERSION_2,
		v2_tls = CURL_HTTP_VERSION_2TLS,
		v3 = CURL_HTTP_VERSION_3
	};

private:
	CURL* curl;
	std::string _responseBody;
	long _responseCode;
	static std::once_flag _isCurlInitialised;

private:
	static std::size_t writeData(char* incomingBuffer, std::size_t size, std::size_t count, std::string* data);
};
